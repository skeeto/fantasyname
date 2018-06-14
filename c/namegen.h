/* Fantasy name generator ANSI C header library
 * This is free and unencumbered software released into the public domain.
 *
 * The compile() function creates a name generator based on an input
 * pattern. The letters s, v, V, c, B, C, i, m, M, D, and d represent
 * different types of random replacements. Everything else is emitted
 * literally.
 *
 *   s - generic syllable
 *   v - vowel
 *   V - vowel or vowel combination
 *   c - consonant
 *   B - consonant or consonant combination suitable for beginning a word
 *   C - consonant or consonant combination suitable anywhere in a word
 *   i - insult
 *   m - mushy name
 *   M - mushy name ending
 *   D - consonant suited for a stupid person's name
 *   d - syllable suited for a stupid person's name (begins with a vowel)
 *
 * All characters between parenthesis () are emitted literally. For
 * example, the pattern "s(dim)", emits a random generic syllable
 * followed by "dim".
 *
 * Characters between angle brackets <> emit patterns from the table
 * above. Imagine the entire pattern is wrapped in one of these.
 *
 * In both types of groupings, a vertical bar | denotes a random choice.
 * Empty groups are allowed. For example, "(foo|bar)" emits either "foo"
 * or "bar". The pattern "<c|v|>" emits a constant, vowel, or nothing at
 * all.
 *
 * An exclamation point ! means to capitalize the component that follows
 * it. For example, "!(foo)" will emit "Foo" and "v!s" will emit a
 * lowercase vowel followed by a capitalized syllable, like "eRod".
 *
 * This library is based on the RinkWorks Fantasy Name Generator.
 * http://www.rinkworks.com/namegen/
 */
#ifndef NAMEGEN_H
#define NAMEGEN_H

#define NAMEGEN_MAX_DEPTH  32 /* Cannot exceed bits in a long */

/* Return codes */
#define NAMEGEN_SUCCESS    0
#define NAMEGEN_TRUNCATED  1  /* Output was truncated */
#define NAMEGEN_INVALID    2  /* Pattern is invalid */
#define NAMEGEN_TOO_DEEP   3  /* Pattern exceeds maximum nesting depth */

/* Generate a name into DST of LEN bytes from PATTERN and using SEED.
 *
 * The length must be non-zero. For best results, the lower 32 bits of
 * the seed should be thoroughly initialized. A particular seed will
 * produce the same results on all platforms.
 *
 * The return value is one of the above codes, indicating success or
 * that something went wrong. Truncation occurs when DST was too short.
 * Pattern is validated even when the output has been truncated.
 */
static int
namegen(char *dst, unsigned long len, const char *pattern, unsigned long *seed);

/* Implementation */

/* Rather than compile the pattern into some internal representation,
 * the name is generated directly from the pattern in a single pass
 * using reservoir sampling. If an alternate option is selected, the
 * output pointer is reset to "undo" the output for the previous group.
 * This means the output buffer may be written beyond the final output
 * length (but never beyond the buffer length).
 *
 * The substitution templates are stored in an efficient, packed form
 * that contains no pointers. This is to avoid cluttering up the
 * relocation table, but without any additional run-time overhead.
 */

/* Return offsets table offset for C, or -1 if not special.
 * The return value is suitable for namegen_offsets().
 */
static int
namegen_special(int c)
{
    static const signed char special[] = {
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1, 0x00, 0x01, 0x02,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1, 0x03,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1, 0x04,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1, 0x05, 0x06,   -1,   -1,   -1,
        -1, 0x07,   -1,   -1,   -1, 0x08,   -1,   -1,
        -1,   -1,   -1, 0x09,   -1,   -1, 0x0a,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1
    };
    if (c >= 0 && c < 128)
        return special[c];
    return -1;
}

/* Return offsets and number of offsets for special N.
 * Offsets point into namegen_argz.
 */
static int
namegen_offsets(int n, const short **offsets)
{
    static const short offsets_table[] = {
        0x0000, 0x0002, 0x0005, 0x0008, 0x000a, 0x000d, 0x0011, 0x0014,
        0x0017, 0x0019, 0x001c, 0x001e, 0x0020, 0x0022, 0x0024, 0x0026,
        0x0028, 0x002b, 0x002d, 0x002f, 0x0031, 0x0034, 0x0037, 0x0039,
        0x003c, 0x003e, 0x0042, 0x0045, 0x0048, 0x004b, 0x004e, 0x0051,
        0x0055, 0x0058, 0x005a, 0x005d, 0x0061, 0x0064, 0x0066, 0x0068,
        0x006b, 0x006d, 0x006f, 0x0072, 0x0074, 0x0076, 0x0079, 0x007c,
        0x007e, 0x0080, 0x0082, 0x0085, 0x0087, 0x0089, 0x008b, 0x008e,
        0x0091, 0x0094, 0x0096, 0x0098, 0x009b, 0x009e, 0x00a1, 0x00a3,
        0x00a6, 0x00a8, 0x00aa, 0x00ad, 0x00b0, 0x00b3, 0x00b5, 0x00b8,
        0x00bb, 0x00be, 0x00c0, 0x00c3, 0x00c5, 0x00c7, 0x00c9, 0x00cb,
        0x00cd, 0x00d0, 0x00d3, 0x00d6, 0x00d8, 0x00da, 0x00dd, 0x00e0,
        0x00e2, 0x00e5, 0x00e8, 0x00eb, 0x00ed, 0x00ef, 0x00f1, 0x00f4,
        0x00f6, 0x00f8, 0x00fa, 0x00fd, 0x00ff, 0x0103, 0x0109, 0x010f,
        0x0114, 0x011a, 0x011f, 0x0127, 0x0130, 0x013a, 0x013f, 0x0144,
        0x0148, 0x014d, 0x0151, 0x0156, 0x015b, 0x0160, 0x0165, 0x0169,
        0x016d, 0x0172, 0x0177, 0x017c, 0x017e, 0x0180, 0x0182, 0x0184,
        0x0186, 0x0188, 0x018b, 0x018e, 0x0191, 0x0194, 0x0197, 0x019a,
        0x019d, 0x01a0, 0x01a3, 0x01a6, 0x01a9, 0x01ac, 0x01af, 0x01b2,
        0x01b5, 0x01b8, 0x01ba, 0x01bc, 0x01be, 0x01c0, 0x01c2, 0x01c4,
        0x01c6, 0x01c8, 0x01ca, 0x01cc, 0x01ce, 0x01d0, 0x01d2, 0x01d4,
        0x01d6, 0x01d8, 0x01da, 0x01dc, 0x01de, 0x01e0, 0x01e2, 0x01e7,
        0x01ed, 0x01f0, 0x01f3, 0x01f6, 0x01fb, 0x01ff, 0x0204, 0x0208,
        0x020c, 0x020f, 0x0213, 0x0217, 0x021b, 0x021f, 0x0223, 0x0227,
        0x022b, 0x022f, 0x0234, 0x0237, 0x023b, 0x023e, 0x0242, 0x0246,
        0x0249, 0x024d, 0x0251, 0x0256, 0x0259, 0x025d, 0x0261, 0x0265,
        0x026a, 0x026e, 0x0272, 0x0276, 0x027c, 0x0281, 0x0286, 0x028b,
        0x028f, 0x0296, 0x029b, 0x02a2, 0x02a7, 0x02ac, 0x02b2, 0x02b7,
        0x02bb, 0x02c0, 0x02c5, 0x02ca, 0x02cf, 0x02d4, 0x02db, 0x02e0,
        0x02e7, 0x02ec, 0x02f4, 0x02f9, 0x02ff, 0x0307, 0x030f, 0x0314,
        0x0319, 0x031e, 0x0323, 0x0328, 0x032e, 0x0332, 0x0337, 0x033b,
        0x0340, 0x0346, 0x034c, 0x0353, 0x035b, 0x0361, 0x0366, 0x036a,
        0x036f, 0x0374, 0x0379, 0x0380, 0x0387, 0x038e, 0x0395, 0x039b,
        0x03a2, 0x03a9, 0x03b0, 0x03b6, 0x03bd, 0x03c3, 0x03c9, 0x03d0,
        0x03d8, 0x03df, 0x03e7, 0x03ee, 0x03f6, 0x03fb, 0x0402, 0x0409,
        0x0413, 0x041d, 0x0427, 0x0431, 0x0438, 0x0441, 0x0448, 0x0450,
        0x0457, 0x045f, 0x0467, 0x046e, 0x0476, 0x047d, 0x0483, 0x048a,
        0x0491, 0x0498, 0x049f, 0x04a5, 0x04ab, 0x04af, 0x04b3, 0x04b6,
        0x04ba, 0x04be, 0x04c2, 0x04c5, 0x04c9, 0x04cc, 0x04d0, 0x04d3,
        0x04d7, 0x04da, 0x04de, 0x04e3, 0x04e6, 0x04ea, 0x04ee, 0x04f2,
        0x04f6, 0x04fa, 0x04fe, 0x0502, 0x0506, 0x050a, 0x050e, 0x0512,
        0x0516, 0x051a, 0x051e, 0x0522, 0x0525, 0x0528, 0x052c, 0x0530,
        0x0535, 0x0538, 0x053c, 0x0540, 0x0543, 0x0547, 0x054b, 0x054f,
        0x0553, 0x0557, 0x055a, 0x055f, 0x0563, 0x0566, 0x056a, 0x056e,
        0x0572, 0x0575, 0x0578, 0x057c, 0x057f, 0x0583, 0x0587, 0x058b,
        0x058f, 0x0593, 0x0597, 0x059b, 0x059f, 0x05a3, 0x05a7, 0x05aa,
        0x05ae, 0x05b2, 0x05b5, 0x05b8, 0x05bb, 0x05bf, 0x05c2, 0x05c7,
        0x05cb, 0x05cf, 0x05d3, 0x05d7, 0x05db, 0x05df, 0x05e3, 0x05e7,
        0x05eb, 0x05ef, 0x05f3, 0x05f8, 0x05fc, 0x0600, 0x0604, 0x0608,
        0x060c, 0x0611, 0x0615, 0x0619, 0x061d, 0x0621, 0x0626, 0x062a,
        0x062e, 0x0632, 0x0636, 0x063a, 0x063d, 0x0641, 0x0645, 0x0649,
        0x064d, 0x0651, 0x0655, 0x0659, 0x065d, 0x0661, 0x0665, 0x0669,
        0x066b, 0x066d, 0x066f, 0x0671, 0x0673
    };
    static const short off_len[] = {
        0x0000, 0x002b, 0x002b, 0x0024, 0x004f, 0x0015, 0x0064, 0x0017,
        0x007b, 0x0016, 0x0091, 0x0015, 0x00a6, 0x0024, 0x00ca, 0x002f,
        0x00f9, 0x002b, 0x0124, 0x0073, 0x0197, 0x0006
    };
    *offsets = offsets_table + off_len[n * 2 + 0];
    return off_len[n * 2 + 1];
}

static const char namegen_argz[] = {
    'b',  0 , 'b', 'l',  0 , 'b', 'r',  0 , 'c',  0 , 'c', 'h',  0 , 'c', 'h',
    'r',  0 , 'c', 'l',  0 , 'c', 'r',  0 , 'd',  0 , 'd', 'r',  0 , 'f',  0 ,
    'g',  0 , 'h',  0 , 'j',  0 , 'k',  0 , 'l',  0 , 'l', 'l',  0 , 'm',  0 ,
    'n',  0 , 'p',  0 , 'p', 'h',  0 , 'q', 'u',  0 , 'r',  0 , 'r', 'h',  0 ,
    's',  0 , 's', 'c', 'h',  0 , 's', 'h',  0 , 's', 'l',  0 , 's', 'm',  0 ,
    's', 'n',  0 , 's', 't',  0 , 's', 't', 'r',  0 , 's', 'w',  0 , 't',  0 ,
    't', 'h',  0 , 't', 'h', 'r',  0 , 't', 'r',  0 , 'v',  0 , 'w',  0 , 'w',
    'h',  0 , 'y',  0 , 'z',  0 , 'z', 'h',  0 , 'b',  0 , 'c',  0 , 'c', 'h',
     0 , 'c', 'k',  0 , 'd',  0 , 'f',  0 , 'g',  0 , 'g', 'h',  0 , 'h',  0 ,
    'k',  0 , 'l',  0 , 'l', 'd',  0 , 'l', 'l',  0 , 'l', 't',  0 , 'm',  0 ,
    'n',  0 , 'n', 'd',  0 , 'n', 'n',  0 , 'n', 't',  0 , 'p',  0 , 'p', 'h',
     0 , 'q',  0 , 'r',  0 , 'r', 'd',  0 , 'r', 'r',  0 , 'r', 't',  0 , 's',
     0 , 's', 'h',  0 , 's', 's',  0 , 's', 't',  0 , 't',  0 , 't', 'h',  0 ,
    'v',  0 , 'w',  0 , 'y',  0 , 'z',  0 , 'b',  0 , 'b', 'l',  0 , 'b', 'r',
     0 , 'c', 'l',  0 , 'd',  0 , 'f',  0 , 'f', 'l',  0 , 'f', 'r',  0 , 'g',
     0 , 'g', 'h',  0 , 'g', 'l',  0 , 'g', 'r',  0 , 'h',  0 , 'j',  0 , 'k',
     0 , 'k', 'l',  0 , 'm',  0 , 'n',  0 , 'p',  0 , 't', 'h',  0 , 'w',  0 ,
    'b', 'o', 'o',  0 , 'b', 'u', 'n', 'c', 'h',  0 , 'b', 'u', 'n', 'n', 'y',
     0 , 'c', 'a', 'k', 'e',  0 , 'c', 'a', 'k', 'e', 's',  0 , 'c', 'u', 't',
    'e',  0 , 'd', 'a', 'r', 'l', 'i', 'n', 'g',  0 , 'd', 'u', 'm', 'p', 'l',
    'i', 'n', 'g',  0 , 'd', 'u', 'm', 'p', 'l', 'i', 'n', 'g', 's',  0 , 'f',
    'a', 'c', 'e',  0 , 'f', 'o', 'o', 'f',  0 , 'g', 'o', 'o',  0 , 'h', 'e',
    'a', 'd',  0 , 'k', 'i', 'n',  0 , 'k', 'i', 'n', 's',  0 , 'l', 'i', 'p',
    's',  0 , 'l', 'o', 'v', 'e',  0 , 'm', 'u', 's', 'h',  0 , 'p', 'i', 'e',
     0 , 'p', 'o', 'o',  0 , 'p', 'o', 'o', 'h',  0 , 'p', 'o', 'o', 'k',  0 ,
    'p', 'u', 'm', 's',  0 , 'a',  0 , 'e',  0 , 'i',  0 , 'o',  0 , 'u',  0 ,
    'y',  0 , 'a', 'e',  0 , 'a', 'i',  0 , 'a', 'u',  0 , 'a', 'y',  0 , 'e',
    'a',  0 , 'e', 'e',  0 , 'e', 'i',  0 , 'e', 'u',  0 , 'e', 'y',  0 , 'i',
    'a',  0 , 'i', 'e',  0 , 'o', 'e',  0 , 'o', 'i',  0 , 'o', 'o',  0 , 'o',
    'u',  0 , 'u', 'i',  0 , 'b',  0 , 'c',  0 , 'd',  0 , 'f',  0 , 'g',  0 ,
    'h',  0 , 'j',  0 , 'k',  0 , 'l',  0 , 'm',  0 , 'n',  0 , 'p',  0 , 'q',
     0 , 'r',  0 , 's',  0 , 't',  0 , 'v',  0 , 'w',  0 , 'x',  0 , 'y',  0 ,
    'z',  0 , 'e', 'l', 'c', 'h',  0 , 'i', 'd', 'i', 'o', 't',  0 , 'o', 'b',
     0 , 'o', 'g',  0 , 'o', 'k',  0 , 'o', 'l', 'p', 'h',  0 , 'o', 'l', 't',
     0 , 'o', 'm', 'p', 'h',  0 , 'o', 'n', 'g',  0 , 'o', 'n', 'k',  0 , 'o',
    'o',  0 , 'o', 'o', 'b',  0 , 'o', 'o', 'f',  0 , 'o', 'o', 'g',  0 , 'o',
    'o', 'k',  0 , 'o', 'o', 'z',  0 , 'o', 'r', 'g',  0 , 'o', 'r', 'k',  0 ,
    'o', 'r', 'm',  0 , 'o', 'r', 'o', 'n',  0 , 'u', 'b',  0 , 'u', 'c', 'k',
     0 , 'u', 'g',  0 , 'u', 'l', 'f',  0 , 'u', 'l', 't',  0 , 'u', 'm',  0 ,
    'u', 'm', 'b',  0 , 'u', 'm', 'p',  0 , 'u', 'm', 'p', 'h',  0 , 'u', 'n',
     0 , 'u', 'n', 'b',  0 , 'u', 'n', 'g',  0 , 'u', 'n', 'k',  0 , 'u', 'n',
    'p', 'h',  0 , 'u', 'n', 't',  0 , 'u', 'z', 'z',  0 , 'a', 'i', 'r',  0 ,
    'a', 'n', 'k', 'l', 'e',  0 , 'b', 'a', 'l', 'l',  0 , 'b', 'e', 'e', 'f',
     0 , 'b', 'o', 'n', 'e',  0 , 'b', 'u', 'm',  0 , 'b', 'u', 'm', 'b', 'l',
    'e',  0 , 'b', 'u', 'm', 'p',  0 , 'c', 'h', 'e', 'e', 's', 'e',  0 , 'c',
    'l', 'o', 'd',  0 , 'c', 'l', 'o', 't',  0 , 'c', 'l', 'o', 'w', 'n',  0 ,
    'c', 'o', 'r', 'n',  0 , 'd', 'i', 'p',  0 , 'd', 'o', 'l', 't',  0 , 'd',
    'o', 'o', 'f',  0 , 'd', 'o', 'r', 'k',  0 , 'd', 'u', 'm', 'b',  0 , 'f',
    'a', 'c', 'e',  0 , 'f', 'i', 'n', 'g', 'e', 'r',  0 , 'f', 'o', 'o', 't',
     0 , 'f', 'u', 'm', 'b', 'l', 'e',  0 , 'g', 'o', 'o', 'f',  0 , 'g', 'r',
    'u', 'm', 'b', 'l', 'e',  0 , 'h', 'e', 'a', 'd',  0 , 'k', 'n', 'o', 'c',
    'k',  0 , 'k', 'n', 'o', 'c', 'k', 'e', 'r',  0 , 'k', 'n', 'u', 'c', 'k',
    'l', 'e',  0 , 'l', 'o', 'a', 'f',  0 , 'l', 'u', 'm', 'p',  0 , 'l', 'u',
    'n', 'k',  0 , 'm', 'e', 'a', 't',  0 , 'm', 'u', 'c', 'k',  0 , 'm', 'u',
    'n', 'c', 'h',  0 , 'n', 'i', 't',  0 , 'n', 'u', 'm', 'b',  0 , 'p', 'i',
    'n',  0 , 'p', 'u', 'f', 'f',  0 , 's', 'k', 'u', 'l', 'l',  0 , 's', 'n',
    'a', 'r', 'k',  0 , 's', 'n', 'e', 'e', 'z', 'e',  0 , 't', 'h', 'i', 'm',
    'b', 'l', 'e',  0 , 't', 'w', 'e', 'r', 'p',  0 , 't', 'w', 'i', 't',  0 ,
    'w', 'a', 'd',  0 , 'w', 'i', 'm', 'p',  0 , 'w', 'i', 'p', 'e',  0 , 'b',
    'a', 'b', 'y',  0 , 'b', 'o', 'o', 'b', 'l', 'e',  0 , 'b', 'u', 'n', 'k',
    'e', 'r',  0 , 'c', 'u', 'd', 'd', 'l', 'e',  0 , 'c', 'u', 'd', 'd', 'l',
    'y',  0 , 'c', 'u', 't', 'i', 'e',  0 , 'd', 'o', 'o', 'd', 'l', 'e',  0 ,
    'f', 'o', 'o', 'f', 'i', 'e',  0 , 'g', 'o', 'o', 'b', 'l', 'e',  0 , 'h',
    'o', 'n', 'e', 'y',  0 , 'k', 'i', 's', 's', 'i', 'e',  0 , 'l', 'o', 'v',
    'e', 'r',  0 , 'l', 'o', 'v', 'e', 'y',  0 , 'm', 'o', 'o', 'f', 'i', 'e',
     0 , 'm', 'o', 'o', 'g', 'l', 'i', 'e',  0 , 'm', 'o', 'o', 'p', 'i', 'e',
     0 , 'm', 'o', 'o', 'p', 's', 'i', 'e',  0 , 'n', 'o', 'o', 'k', 'u', 'm',
     0 , 'p', 'o', 'o', 'c', 'h', 'i', 'e',  0 , 'p', 'o', 'o', 'f',  0 , 'p',
    'o', 'o', 'f', 'i', 'e',  0 , 'p', 'o', 'o', 'k', 'i', 'e',  0 , 's', 'c',
    'h', 'm', 'o', 'o', 'p', 'i', 'e',  0 , 's', 'c', 'h', 'n', 'o', 'o', 'g',
    'l', 'e',  0 , 's', 'c', 'h', 'n', 'o', 'o', 'k', 'i', 'e',  0 , 's', 'c',
    'h', 'n', 'o', 'o', 'k', 'u', 'm',  0 , 's', 'm', 'o', 'o', 'c', 'h',  0 ,
    's', 'm', 'o', 'o', 'c', 'h', 'i', 'e',  0 , 's', 'm', 'o', 'o', 's', 'h',
     0 , 's', 'n', 'o', 'o', 'g', 'l', 'e',  0 , 's', 'n', 'o', 'o', 'g', 'y',
     0 , 's', 'n', 'o', 'o', 'k', 'i', 'e',  0 , 's', 'n', 'o', 'o', 'k', 'u',
    'm',  0 , 's', 'n', 'u', 'g', 'g', 'y',  0 , 's', 'w', 'e', 'e', 't', 'i',
    'e',  0 , 'w', 'o', 'o', 'g', 'l', 'e',  0 , 'w', 'o', 'o', 'g', 'y',  0 ,
    'w', 'o', 'o', 'k', 'i', 'e',  0 , 'w', 'o', 'o', 'k', 'u', 'm',  0 , 'w',
    'u', 'd', 'd', 'l', 'e',  0 , 'w', 'u', 'd', 'd', 'l', 'y',  0 , 'w', 'u',
    'g', 'g', 'y',  0 , 'w', 'u', 'n', 'n', 'y',  0 , 'a', 'c', 'h',  0 , 'a',
    'c', 'k',  0 , 'a', 'd',  0 , 'a', 'g', 'e',  0 , 'a', 'l', 'd',  0 , 'a',
    'l', 'e',  0 , 'a', 'n',  0 , 'a', 'n', 'g',  0 , 'a', 'r',  0 , 'a', 'r',
    'd',  0 , 'a', 's',  0 , 'a', 's', 'h',  0 , 'a', 't',  0 , 'a', 't', 'h',
     0 , 'a', 'u', 'g', 'h',  0 , 'a', 'w',  0 , 'b', 'a', 'n',  0 , 'b', 'e',
    'l',  0 , 'b', 'u', 'r',  0 , 'c', 'e', 'r',  0 , 'c', 'h', 'a',  0 , 'c',
    'h', 'e',  0 , 'd', 'a', 'n',  0 , 'd', 'a', 'r',  0 , 'd', 'e', 'l',  0 ,
    'd', 'e', 'n',  0 , 'd', 'r', 'a',  0 , 'd', 'y', 'n',  0 , 'e', 'c', 'h',
     0 , 'e', 'l', 'd',  0 , 'e', 'l', 'm',  0 , 'e', 'm',  0 , 'e', 'n',  0 ,
    'e', 'n', 'd',  0 , 'e', 'n', 'g',  0 , 'e', 'n', 't', 'h',  0 , 'e', 'r',
     0 , 'e', 's', 's',  0 , 'e', 's', 't',  0 , 'e', 't',  0 , 'g', 'a', 'r',
     0 , 'g', 'h', 'a',  0 , 'h', 'a', 't',  0 , 'h', 'i', 'n',  0 , 'h', 'o',
    'n',  0 , 'i', 'a',  0 , 'i', 'g', 'h', 't',  0 , 'i', 'l', 'd',  0 , 'i',
    'm',  0 , 'i', 'n', 'a',  0 , 'i', 'n', 'e',  0 , 'i', 'n', 'g',  0 , 'i',
    'r',  0 , 'i', 's',  0 , 'i', 's', 's',  0 , 'i', 't',  0 , 'k', 'a', 'l',
     0 , 'k', 'e', 'l',  0 , 'k', 'i', 'm',  0 , 'k', 'i', 'n',  0 , 'l', 'e',
    'r',  0 , 'l', 'o', 'r',  0 , 'l', 'y', 'e',  0 , 'm', 'o', 'r',  0 , 'm',
    'o', 's',  0 , 'n', 'a', 'l',  0 , 'n', 'y',  0 , 'n', 'y', 's',  0 , 'o',
    'l', 'd',  0 , 'o', 'm',  0 , 'o', 'n',  0 , 'o', 'r',  0 , 'o', 'r', 'm',
     0 , 'o', 's',  0 , 'o', 'u', 'g', 'h',  0 , 'p', 'e', 'r',  0 , 'p', 'o',
    'l',  0 , 'q', 'u', 'a',  0 , 'q', 'u', 'e',  0 , 'r', 'a', 'd',  0 , 'r',
    'a', 'k',  0 , 'r', 'a', 'n',  0 , 'r', 'a', 'y',  0 , 'r', 'i', 'l',  0 ,
    'r', 'i', 's',  0 , 'r', 'o', 'd',  0 , 'r', 'o', 't', 'h',  0 , 'r', 'y',
    'n',  0 , 's', 'a', 'm',  0 , 's', 'a', 'y',  0 , 's', 'e', 'r',  0 , 's',
    'h', 'y',  0 , 's', 'k', 'e', 'l',  0 , 's', 'u', 'l',  0 , 't', 'a', 'i',
     0 , 't', 'a', 'n',  0 , 't', 'a', 's',  0 , 't', 'h', 'e', 'r',  0 , 't',
    'i', 'a',  0 , 't', 'i', 'n',  0 , 't', 'o', 'n',  0 , 't', 'o', 'r',  0 ,
    't', 'u', 'r',  0 , 'u', 'm',  0 , 'u', 'n', 'd',  0 , 'u', 'n', 't',  0 ,
    'u', 'r', 'n',  0 , 'u', 's', 'k',  0 , 'u', 's', 't',  0 , 'v', 'e', 'r',
     0 , 'v', 'e', 's',  0 , 'v', 'o', 'r',  0 , 'w', 'a', 'r',  0 , 'w', 'o',
    'r',  0 , 'y', 'e', 'r',  0 , 'a',  0 , 'e',  0 , 'i',  0 , 'o',  0 , 'u',
     0 , 'y',  0
};

static unsigned long
namegen_rand32(unsigned long *s)
{
    unsigned long x = *s;
    x ^= x << 13;
    x ^= (x & 0xffffffffUL) >> 17;
    x ^= x << 5;
    return (*s = x) & 0xffffffffUL;
}

static int
namegen_cap(int c, int capitalize)
{
    return capitalize && c >= 'a' && c <= 'z' ? c & ~0x20 : c;
}

/* Copy a random substitution for template C into P, but only before E.
 */
static char *
namegen_copy(char *p, char *e, int c, unsigned long *seed, int capitalize)
{
    int n = namegen_special(c);
    if (n == -1) {
        if (p != e)
            *p++ = namegen_cap(c, capitalize);
    } else {
        const short *offsets;
        int count = namegen_offsets(n, &offsets);
        int select = namegen_rand32(seed) % count;
        const char *s = namegen_argz + offsets[select];
        while (*s) {
            int r = *s++;
            if (p != e)
                *p++ = namegen_cap(r, capitalize);
            capitalize = 0;
        }
    }
    return p;
}

static int
namegen(char *dst, unsigned long len, const char *pattern, unsigned long *seed)
{
    int depth = 0;               /* Current nesting depth */
    char *p = dst;               /* Current output pointer */
    char *e = dst + len;         /* Maxiumum output pointer */
    int capitalize = 0;          /* Capitalize next item */

    /* Stacks */
    char *reset[NAMEGEN_MAX_DEPTH];     /* Reset pointer (undo generate) */
    unsigned long n[NAMEGEN_MAX_DEPTH]; /* Number of groups */
    unsigned long silent = 0;    /* Actively generating? */
    unsigned long literal = 0;   /* Current "mode" */
    unsigned long capstack = 0;  /* Initial capitalization state */

    n[0] = 1;
    reset[0] = dst;
    for (; *pattern; pattern++) {
        unsigned long bit; /* Bit for current depth */
        int c = *pattern;
        switch (c) {
            case '<':
                if (++depth == NAMEGEN_MAX_DEPTH) {
                    *dst = 0;
                    return NAMEGEN_TOO_DEEP;
                }
                bit = 1UL << depth;
                n[depth] = 1;
                reset[depth] = p;
                literal &= ~bit;
                silent &= ~bit;
                silent |= (silent << 1) & bit;
                capstack &= ~bit;
                capstack |= (unsigned long)capitalize << depth;
                break;

            case '(':
                if (++depth == NAMEGEN_MAX_DEPTH) {
                    *dst = 0;
                    return NAMEGEN_TOO_DEEP;
                }
                bit = 1UL << depth;
                n[depth] = 1;
                reset[depth] = p;
                literal |= bit;
                silent &= ~bit;
                silent |= (silent << 1) & bit;
                capstack &= ~bit;
                capstack |= (unsigned long)capitalize << depth;
                break;

            case '>':
                if (depth == 0) {
                    *dst = 0;
                    return NAMEGEN_INVALID;
                }
                bit = 1UL << depth--;
                if (literal & bit) {
                    *dst = 0;
                    return NAMEGEN_INVALID;
                }
                break;

            case ')':
                if (depth == 0) {
                    *dst = 0;
                    return NAMEGEN_INVALID;
                }
                bit = 1UL << depth--;
                if (!(literal & bit)) {
                    *dst = 0;
                    return NAMEGEN_INVALID;
                }
                break;

            case '|':
                bit = 1UL << depth;
                /* Stay silent if parent group is silent */
                if (!(silent & (bit >> 1))) {
                    if (namegen_rand32(seed) < 0xffffffffUL / ++n[depth]) {
                        /* Switch to this option */
                        p = reset[depth];
                        silent &= ~bit;
                        capitalize = !!(capstack & bit);
                    } else {
                        /* Skip this option */
                        silent |= bit;
                    }
                }
                break;

            case '!':
                capitalize = 1;
                break;

            default:
                bit = 1UL << depth;
                if (!(silent & bit)) {
                    if (literal & bit) {
                        /* Copy value literally */
                        if (p != e)
                            *p++ = namegen_cap(c, capitalize);
                    } else {
                        /* Copy a substitution */
                        p = namegen_copy(p, e, c, seed, capitalize);
                    }
                }
                capitalize = 0;
        }
    }

    if (depth) {
        *dst = 0;
        return NAMEGEN_INVALID;
    } else if (p == e) {
        p[-1] = 0;
        return NAMEGEN_TRUNCATED;
    } else {
        *p = 0;
        return NAMEGEN_SUCCESS;
    }
}

#endif
