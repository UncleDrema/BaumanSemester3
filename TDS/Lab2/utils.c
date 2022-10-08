// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/11/22.
//

#include "utils.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

err_t string_to_int(char *str, int *out)
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
            return ARGS_ERR;
        }
        num = TO_DIGIT(*str) + num * 10;
        str++;
    }

    *out = num * sign;
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

void copy_file(FILE *from, FILE *to)
{
    char            buffer[BUFSIZ];
    size_t          n;

    while ((n = fread(buffer, sizeof(char), sizeof(buffer), from)) > 0)
    {
        fwrite(buffer, sizeof(char), n, to);
    }
}

void remove_nl(char *str)
{
    char *nl = strchr(str, '\n');
    if (nl != NULL)
    {
        *nl = '\0';
    }
}