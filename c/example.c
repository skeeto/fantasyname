#include "namegen.h"
#include <time.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static unsigned long
hash32(unsigned long a)
{
    a = a & 0xffffffffUL;
    a = (a ^ 61UL) ^ (a >> 16);
    a = (a + (a << 3)) & 0xffffffffUL;
    a = a ^ (a >> 4);
    a = (a * 0x27d4eb2dUL) & 0xffffffffUL;
    a = a ^ (a >> 15);
    return a;
}

#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

#define TEST(s, x) \
    do { \
        if (x) { \
            printf(C_GREEN("PASS") " %s\n", s); \
            count_pass++; \
        } else { \
            printf(C_RED("FAIL") " %s\n", s); \
            count_fail++; \
        } \
    } while (0)

static void
tests(void)
{
    int r;
    char buf[256];
    int count_pass = 0;
    int count_fail = 0;
    unsigned long rng[] = {0xd22bfb3b};

    {
        int i;
        int mismatch = 0;
        int seen[3] = {0, 0, 0};
        for (i = 0; i < 100; i++) {
            memset(buf, 0x5a, sizeof(buf));
            r = namegen(buf, sizeof(buf), "0|1|2", rng);
            if (r != NAMEGEN_SUCCESS || buf[1] || !strchr("012", buf[0])) {
                mismatch++;
            } else {
                seen[buf[0] - '0']++;
            }
        }
        TEST("alternation", !mismatch && seen[0] && seen[1] && seen[2]);
    }

    {
        int i;
        int mismatch = 0;
        int seen[6] = {0, 0, 0};
        for (i = 0; i < 100; i++) {
            memset(buf, 0x5a, sizeof(buf));
            r = namegen(buf, sizeof(buf), "(v)v", rng);
            if (r != NAMEGEN_SUCCESS || buf[0] != 'v' || !buf[1] || buf[2]) {
                mismatch++;
            } else {
                char *p = "aeiouy";
                char *s = strchr(p, buf[1]);
                if (!s)
                    mismatch++;
                else
                    seen[s - p]++;
            }
        }
        for (i = 0; i < 6; i++)
            mismatch += !seen[i];
        TEST("substitution", !mismatch);
    }

    {
        r = namegen(buf, sizeof(buf), "a>", rng);
        TEST("closing bracket", r == NAMEGEN_INVALID);
    }

    {
        r = namegen(buf, sizeof(buf), "a)", rng);
        TEST("closing paren", r == NAMEGEN_INVALID);
    }

    {
        r = namegen(buf, sizeof(buf), "<a)", rng);
        TEST("mismatch paren", r == NAMEGEN_INVALID);
    }

    {
        r = namegen(buf, sizeof(buf), "(a>", rng);
        TEST("mismatch bracket", r == NAMEGEN_INVALID);
    }

    {
        r = namegen(buf, sizeof(buf), "<a", rng);
        TEST("unclosed bracket", r == NAMEGEN_INVALID);
    }

    {
        r = namegen(buf, sizeof(buf), "(a", rng);
        TEST("unclosed paren", r == NAMEGEN_INVALID);
    }

    {
        char *p = "(((((<(((((((((((((((a)))))))))))))))>)))))";
        memset(buf, 0x5a, sizeof(buf));
        r = namegen(buf, sizeof(buf), p, rng);
        TEST("deep nesting", r == NAMEGEN_SUCCESS && !strcmp(buf, "a"));
    }

    {
        memset(buf, 0x5a, sizeof(buf));
        r = namegen(buf, 4, "(abcdefg)", rng);
        TEST("truncation 1",
             r == NAMEGEN_TRUNCATED && !strcmp(buf, "abc") && buf[4] == 0x5a);
    }

    {
        memset(buf, 0x5a, sizeof(buf));
        r = namegen(buf, 2, "i", rng);
        TEST("truncation 2",
             r == NAMEGEN_TRUNCATED && buf[0] && !buf[1] && buf[2] == 0x5a);
    }

    {
        r = namegen(buf, sizeof(buf), "!(foo)", rng);
        TEST("capitalization 1", r == NAMEGEN_SUCCESS && !strcmp(buf, "Foo"));
    }

    {
        r = namegen(buf, sizeof(buf), "(!foo)", rng);
        TEST("capitalization 2", r == NAMEGEN_SUCCESS && !strcmp(buf, "Foo"));
    }

    {
        r = namegen(buf, sizeof(buf), "(f!oo)", rng);
        TEST("capitalization 3", r == NAMEGEN_SUCCESS && !strcmp(buf, "fOo"));
    }

    {
        memset(buf, 0x5a, sizeof(buf));
        r = namegen(buf, sizeof(buf), "", rng);
        TEST("empty", r == NAMEGEN_SUCCESS && !buf[0] && buf[1] == 0x5a);
    }

    if (count_fail)
        exit(EXIT_FAILURE);
    printf("All %d tests passed\n", count_pass);
    exit(EXIT_SUCCESS);
}

int
main(int argc, char **argv)
{
    int i;
    int count = 1;
    FILE *urandom;
    unsigned char randbuf[4];
    unsigned long seed[] = {0x8af611acUL};

    /* Parse command line arguments */
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <pattern> [num]\n", argv[0]);
        printf("  pattern   template for names to generate\n");
        printf("  num       number of names to generate\n");
        exit(EXIT_FAILURE);
    } else if (argc == 3) {
        count = atoi(argv[2]);
    }

    if (!strcmp(argv[1], "--test"))
        tests();

    /* Shuffle up the seed a bit */
    urandom = fopen("/dev/urandom", "rb");
    if (urandom && fread(randbuf, sizeof(randbuf), 1, urandom)) {
        unsigned long rnd =
            (unsigned long)randbuf[0] <<  0 |
            (unsigned long)randbuf[1] <<  8 |
            (unsigned long)randbuf[2] << 16 |
            (unsigned long)randbuf[3] << 24;
        *seed ^= rnd;
        fclose(urandom);
    } else {
        void *p = malloc(4UL * 1024 * 1024);
        *seed ^= hash32(time(0));             /* Current time */
        *seed ^= hash32((ptrdiff_t)main);     /* ASLR entopy */
        *seed ^= hash32((ptrdiff_t)seed);     /* Stack gap entropy */
        *seed ^= hash32((ptrdiff_t)p);        /* Allocator entropy */
        *seed ^= hash32((ptrdiff_t)malloc);   /* C library ASLR */
        free(p);
    }

    /* Generate some names */
    for (i = 0; i < count; i++) {
        char buf[256];
        int r = namegen(buf, sizeof(buf), argv[1], seed);
        if (r == NAMEGEN_INVALID) {
            fprintf(stderr, "%s: invalid pattern\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        printf("%s\n", buf);
    }
    return 0;
}
