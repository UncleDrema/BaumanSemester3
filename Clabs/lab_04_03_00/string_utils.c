#include "string_utils.h"
#include <string.h>

int split(char *string, char **words, char *delim)
{
    char **init_words = words;
    char *word;

    word = strtok(string, delim);

    while (word != NULL)
    {
        *(words++) = word;
        word = strtok(NULL, delim);
    }

    return words - init_words;
}

int filter_words_remove(char **words, int w_count, char *remove_word, char **filtered_words)
{
    char **init_filtered = filtered_words;
    for (int i = 0; i < w_count; i++)
    {
        if (strcmp(words[i], remove_word))
            *(filtered_words++) = words[i];
    }

    return filtered_words - init_filtered;
}

char *remove_symbol_occures_skip_n(char *str, char symbol, int n)
{
    int i = 0;
    int j = i;

    while (str[i])
    {
        if (i < n || str[i] != symbol)
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';

    return str;
}
