//
// Created by archdrema on 9/11/22.
//

#include "utils.h"
#include <ctype.h>

FUNC(int, err_string_to_int, char *str)
{
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
            THROW(NOT_A_NUMBER, 0);
        }
        num = TO_DIGIT(*str) + num * 10;
        str++;
    }
    return num * sign;
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