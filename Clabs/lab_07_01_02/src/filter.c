// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/25/22.
// Реализация функций фильтрации

#include <filter.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>

int get_first_negative_index(const int *pb, const int *pe)
{
    if (pb == NULL || pe == NULL || pe <= pb)
    {
        return ERR_WRONG_ARGS;
    }

    const int *p;
    for (p = pb; p < pe && *p >= 0; p++);

    return p - pb; // NOLINT(cppcoreguidelines-narrowing-conversions) because need the int type for key function
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_dst == NULL || pe_dst == NULL || pb_src > pe_src)
    {
        return ERR_WRONG_ARGS;
    }

    int n = get_first_negative_index(pb_src, pe_src);

    if (n == 0)
    {
        return ERR_DATA;
    }

    *pb_dst = malloc(n * sizeof(int));

    if (*pb_dst == NULL)
    {
        return ERR_MEMORY;
    }

    *pe_dst = *pb_dst + n;
    memcpy(*pb_dst, pb_src, n * sizeof(int));

    return OK;
}
