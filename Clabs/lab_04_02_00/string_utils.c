#include "string_utils.h"
#include <string.h>
#define NO_DELIM 0
#define DELIM_OCCURED 1
#define CONTAINS 1
#define NOT_CONTAINS 0
#define FOUND 1
#define NOT_FOUND 0

int get_unique_words(char **words, int w_count, char **uniques)
{
    int unique_count = 0;
    char *cur_word;

    for (int i = 0; i < w_count; i++)
    {
        cur_word = words[i];

        if (count_str_in_str_arr(uniques, unique_count, cur_word) == 0)
        {
            uniques[unique_count++] = cur_word;
        }
    }

    return unique_count;
}

int count_str_in_str_arr(char **str_arr, int str_count, char *str)
{
    int count = 0;
    for (int i = 0; i < str_count; i++)
    {
        if (!strcmp(str_arr[i], str))
            count++;
    }

    return count;
}

int str_contains_sym(char *string, char symbol)
{
    int state = NOT_CONTAINS;
    while (*string && state == NOT_CONTAINS)
        state = *(string++) == symbol ? CONTAINS : NOT_CONTAINS;
    return state;
}

int split(char *string, char **words, char *delims)
{
    char **init_words = words, *cur_word = *words, cur;
    int state = NO_DELIM;
    int word_found = NOT_FOUND;
    while (*string && str_contains_sym(delims, *string))
        string++;
    while (*string)
    {
        cur = *string;

        if (str_contains_sym(delims, cur))
        {
            state = DELIM_OCCURED;
        }
        else
        {
            if (state == DELIM_OCCURED)
            {
                *cur_word = '\0';
                state = NO_DELIM;
                cur_word = *(++words);
            }

            word_found = FOUND;
            *(cur_word++) = cur;
        }
        string++;
    }


    if (word_found)
    {
        *cur_word = '\0';
        words++;
    }

    return words - init_words;
}
