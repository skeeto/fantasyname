#include "namegen.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static void
mix(unsigned long *seed, unsigned long entropy)
{
    int i;
    *seed ^= entropy;
    for (i = 0; i < 1000; i++)
        namegen_rand32(seed);
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
        mix(seed, time(0));             /* Current time */
        mix(seed, (unsigned long)main); /* ASLR entopy */
        mix(seed, (unsigned long)seed); /* Stack gap entropy */
        mix(seed, (unsigned long)p);    /* Allocator entropy */
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
