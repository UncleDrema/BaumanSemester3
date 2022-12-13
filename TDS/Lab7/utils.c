//
// Created by archdrema on 11/17/22.
//

#include "utils.h"
#include <unistd.h>
#include <openssl/rand.h>

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

char *str_without_repeating(const char *str)
{
    size_t all_chars[UCHAR_MAX + 1];
    for (int i = 0; i <= UCHAR_MAX; i++)
    {
        all_chars[i] = 0;
    }

    const char *ptr = str;
    while (*ptr)
    {
        all_chars[*ptr]++;
        ptr++;
    }

    size_t new_size = 0;
    for (int i = 0; i <= UCHAR_MAX; i++)
    {
        if (all_chars[i] == 1)
        {
            new_size++;
        }
    }

    char *new_str = malloc(new_size + 1);
    new_str[new_size] = '\0';

    size_t i = 0;
    while (*str)
    {
        if (all_chars[*str] == 1)
        {
            new_str[i++] = *str;
        }
        str++;
    }

    return new_str;
}

static inline int rand_range(int min, int max)
{
    return rand() % (max - min) + min;
}

char *rand_str(size_t size)
{
    char *res = malloc(size + 1);
    if (res)
    {
        for (size_t i = 0; i < size; i++)
        {
            char ch = (char) rand_range('!', '~');
            while (ch == '<' || ch == '>' || ch == '&')
            {
                ch = (char) rand_range('!', '~');
            }
            res[i] = ch;
        }
    }
    return res;
}

size_t count_str(char *str, char ch, size_t *cmp_count)
{
    *cmp_count = 0;
    size_t count = 0;
    while (*str)
    {
        (*cmp_count)++;
        if (*str == ch)
        {
            count++;
        }
        str++;
    }
    return count;
}