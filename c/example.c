#include "namegen.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

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

int
main(int argc, char **argv)
{
    int i;
    int count = 1;
    FILE *urandom;
    unsigned char buf[4];
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

    /* Shuffle up the seed a bit */
    urandom = fopen("/dev/urandom", "rb");
    if (urandom && fread(buf, sizeof(buf), 1, urandom)) {
        unsigned long rnd =
            (unsigned long)buf[0] <<  0 |
            (unsigned long)buf[1] <<  8 |
            (unsigned long)buf[2] << 16 |
            (unsigned long)buf[3] << 24;
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
