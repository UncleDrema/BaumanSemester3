//
// Created by archdrema on 11/17/22.
//

#include "utils.h"
#include <unistd.h>
#include <openssl/rand.h>

#define MILLION 1000000

static double random_double()
{
    union
    {
        uint64_t i;
        unsigned char c[sizeof(uint64_t)];
    } u;

    if (!RAND_bytes(u.c, sizeof(u.c)))
        exit(1);
    return ((u.i >> 11) * (1.0/9007199254740992.0));
} ((u.i >> 11) * (1.0/9007199254740992.0));
}

double rand_range(double min, double max)
{
    if (max - min == 0)
    {
        return min;
    }
    return (max - min) * random_double() + min;
}

int skip_to_nl(FILE *f)
{
    int ch, skipped = 0;
    do
    {
        ch = getc(f);
        skipped++;
    }
    while (ch != '\n' && ch != EOF);
    return skipped;
}

double abs_err(double expected, double measured)
{
    return (measured - expected) / expected;
}