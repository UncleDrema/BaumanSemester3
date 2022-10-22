// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
//
// Created by archdrema on 10/9/22.
//

#include <utils.h>

#define ABS(a) ((a >= 0) ? (a) : (-(a)))

int float_eq(float a, float b, float tol)
{
    return ABS(a - b) <= tol;
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