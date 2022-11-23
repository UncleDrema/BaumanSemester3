// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 10/28/22.
// Реализация вспомогательных функций

#include <utils.h>
#include <ctype.h>

err_t string_to_int(char *str, int *res)
{
    if (str == NULL || res == NULL || *str == '\0')
    {
        return NOT_A_NUMBER;
    }
    int sign = 1;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    int num = 0;
    while (*str)
    {
        if (!isdigit(*str))
        {
            return NOT_A_NUMBER;
        }
        num = TO_DIGIT(*str) + num * 10;
        str++;
    }
    *res = num * sign;
    return OK;
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