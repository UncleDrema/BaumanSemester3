// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/25/22.
// Реализация функций-компараторов

#include <comparators.h>

int int_comparator(const void *a, const void *b)
{
    int a_val = *((int *) a);
    int b_val = *((int *) b);
    return (a_val < b_val) ? -1 : ((a_val > b_val) ? 1 : 0);
}

int double_comparator(const void *a, const void *b)
{
    double a_val = *((double *) a);
    double b_val = *((double *) b);
    return (a_val < b_val) ? -1 : ((a_val > b_val) ? 1 : 0);
}
