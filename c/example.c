#include "namegen.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    int i;
    void *p;
    int count = 1;
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
    *seed ^= time(0);
    for (i = 0; i < 1000; i++)
        namegen_rand32(seed);
    *seed ^= (unsigned long)main; /* ASLR entopy */
    for (i = 0; i < 1000; i++)
        namegen_rand32(seed);
    *seed ^= (unsigned long)seed; /* Stack gap entropy */
    for (i = 0; i < 1000; i++)
        namegen_rand32(seed);
    p = malloc(1);
    *seed ^= (unsigned long)p;    /* Allocator entropy */
    free(p);
    for (i = 0; i < 1000; i++)
        namegen_rand32(seed);

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
