#!/usr/bin/env python3

# This script generates the lookup tables in namegen.h. To change those
# tables, modify the symbols dictionary in this script, execute it to
# generate the new tables, then replace the tables in the C source.

symbols = {
    's': [
        'ach', 'ack', 'ad', 'age', 'ald', 'ale', 'an', 'ang', 'ar', 'ard',
        'as', 'ash', 'at', 'ath', 'augh', 'aw', 'ban', 'bel', 'bur', 'cer',
        'cha', 'che', 'dan', 'dar', 'del', 'den', 'dra', 'dyn', 'ech', 'eld',
        'elm', 'em', 'en', 'end', 'eng', 'enth', 'er', 'ess', 'est', 'et',
        'gar', 'gha', 'hat', 'hin', 'hon', 'ia', 'ight', 'ild', 'im', 'ina',
        'ine', 'ing', 'ir', 'is', 'iss', 'it', 'kal', 'kel', 'kim', 'kin',
        'ler', 'lor', 'lye', 'mor', 'mos', 'nal', 'ny', 'nys', 'old', 'om',
        'on', 'or', 'orm', 'os', 'ough', 'per', 'pol', 'qua', 'que', 'rad',
        'rak', 'ran', 'ray', 'ril', 'ris', 'rod', 'roth', 'ryn', 'sam', 'say',
        'ser', 'shy', 'skel', 'sul', 'tai', 'tan', 'tas', 'ther', 'tia', 'tin',
        'ton', 'tor', 'tur', 'um', 'und', 'unt', 'urn', 'usk', 'ust', 'ver',
        'ves', 'vor', 'war', 'wor', 'yer'
    ],
    'v': ['a', 'e', 'i', 'o', 'u', 'y'],
    'V': [
        'a', 'e', 'i', 'o', 'u', 'y', 'ae', 'ai', 'au', 'ay', 'ea', 'ee', 'ei',
        'eu', 'ey', 'ia', 'ie', 'oe', 'oi', 'oo', 'ou', 'ui'
    ],
    'c': [
        'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r',
        's', 't', 'v', 'w', 'x', 'y', 'z'
    ],
    'B': [
        'b', 'bl', 'br', 'c', 'ch', 'chr', 'cl', 'cr', 'd', 'dr', 'f', 'g',
        'h', 'j', 'k', 'l', 'll', 'm', 'n', 'p', 'ph', 'qu', 'r', 'rh', 's',
        'sch', 'sh', 'sl', 'sm', 'sn', 'st', 'str', 'sw', 't', 'th', 'thr',
        'tr', 'v', 'w', 'wh', 'y', 'z', 'zh'
    ],
    'C': [
        'b', 'c', 'ch', 'ck', 'd', 'f', 'g', 'gh', 'h', 'k', 'l', 'ld', 'll',
        'lt', 'm', 'n', 'nd', 'nn', 'nt', 'p', 'ph', 'q', 'r', 'rd', 'rr',
        'rt', 's', 'sh', 'ss', 'st', 't', 'th', 'v', 'w', 'y', 'z'
    ],
    'i': [
        'air', 'ankle', 'ball', 'beef', 'bone', 'bum', 'bumble', 'bump',
        'cheese', 'clod', 'clot', 'clown', 'corn', 'dip', 'dolt', 'doof',
        'dork', 'dumb', 'face', 'finger', 'foot', 'fumble', 'goof', 'grumble',
        'head', 'knock', 'knocker', 'knuckle', 'loaf', 'lump', 'lunk', 'meat',
        'muck', 'munch', 'nit', 'numb', 'pin', 'puff', 'skull', 'snark',
        'sneeze', 'thimble', 'twerp', 'twit', 'wad', 'wimp', 'wipe'
    ],
    'm': [
        'baby', 'booble', 'bunker', 'cuddle', 'cuddly', 'cutie', 'doodle',
        'foofie', 'gooble', 'honey', 'kissie', 'lover', 'lovey', 'moofie',
        'mooglie', 'moopie', 'moopsie', 'nookum', 'poochie', 'poof', 'poofie',
        'pookie', 'schmoopie', 'schnoogle', 'schnookie', 'schnookum', 'smooch',
        'smoochie', 'smoosh', 'snoogle', 'snoogy', 'snookie', 'snookum',
        'snuggy', 'sweetie', 'woogle', 'woogy', 'wookie', 'wookum', 'wuddle',
        'wuddly', 'wuggy', 'wunny'
    ],
    'M': [
        'boo', 'bunch', 'bunny', 'cake', 'cakes', 'cute', 'darling',
        'dumpling', 'dumplings', 'face', 'foof', 'goo', 'head', 'kin', 'kins',
        'lips', 'love', 'mush', 'pie', 'poo', 'pooh', 'pook', 'pums'
    ],
    'D': [
        'b', 'bl', 'br', 'cl', 'd', 'f', 'fl', 'fr', 'g', 'gh', 'gl', 'gr',
        'h', 'j', 'k', 'kl', 'm', 'n', 'p', 'th', 'w'
    ],
    'd': [
        'elch', 'idiot', 'ob', 'og', 'ok', 'olph', 'olt', 'omph', 'ong', 'onk',
        'oo', 'oob', 'oof', 'oog', 'ook', 'ooz', 'org', 'ork', 'orm', 'oron',
        'ub', 'uck', 'ug', 'ulf', 'ult', 'um', 'umb', 'ump', 'umph', 'un',
        'unb', 'ung', 'unk', 'unph', 'unt', 'uzz'
    ]
}

argz = []     # Concatenation of all strings, including null terminators
offsets = []  # Offset into argz of the Nth string
off_len = []  # Offset/length into offsets of the Nth special character
special = []  # ASCII table of offsets into off_len

offset = 0
keys = sorted(symbols.keys())
for c in keys:
    options = symbols[c]
    off_len.append(len(argz))
    off_len.append(len(options))
    for option in options:
        offsets.append(offset)
        offset = offset + len(option) + 1
        argz.append(option)

for c in range(0, 128):
    try:
        special.append(keys.index(chr(c)))
    except ValueError:
        special.append(-1)

# Prints a C array initializer
def dump(values, fmt, width):
    for i, v in enumerate(values):
        if i > 0:
            print(',', end='')
        if i % width == 0:
            print('\n    ', end='')
        else:
            print(' ', end='')
        print(fmt(v), end='');
    print('\n};\n')

print('static const signed char special[] = {', end='')
dump(special, lambda v: '  -1' if v < 0 else '0x%02x' % v, 8)

print('static const short offsets_table[] = {', end='')
dump(offsets, lambda v: '0x%04x' % v, 8)

print('static const short off_len[] = {', end='')
dump(off_len, lambda v: '0x%04x' % v, 8)

print('static const char namegen_argz[] = {', end='')
dump('\0'.join(argz) + '\0', lambda v: ' 0 ' if v == '\0' else "'%c'" % v, 15)
