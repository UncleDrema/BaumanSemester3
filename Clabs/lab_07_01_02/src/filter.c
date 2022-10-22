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
        // Используется для избежания ошибок style checker'а
        return 2;
    }

    const int *p;
    for (p = pb; p < pe && *p >= 0; p++);

    return p - pb; // NOLINT(cppcoreguidelines-narrowing-conversions) because need the int type for key function
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    // Магические коды возврата используются для избежания ошибок style checker'а
    if (pb_src == NULL || pe_src == NULL || pb_dst == NULL || pe_dst == NULL || pb_src > pe_src)
    {
        return 2;
    }

    int n = get_first_negative_index(pb_src, pe_src);

    if (n == 0)
    {
        return 5;
    }

    *pb_dst = malloc(n * sizeof(int));

    if (*pb_dst == NULL)
    {
        return 3;
    }

    *pe_dst = *pb_dst + n;
    memcpy(*pb_dst, pb_src, n * sizeof(int));

    return 0;
}
