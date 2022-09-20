#include <stdio.h>
#include <string.h>
#include "string_utils.h"
#define BUF_SIZE 258
#define ERR_NO_WORDS 1
#define ERR_EOF 2
#define ERR_BUF 3
#define ERR_NO_WORDS_PROCESSED 4
#define OK 0

char *join_reversed_processed(char **words, int w_count, char *destination);

int main(void)
{
    int return_code = OK;
    char string[BUF_SIZE];

    string[BUF_SIZE - 2] = '\0';

    fgets(string, BUF_SIZE, stdin);

    if (feof(stdin))
    {
        return_code = ERR_EOF;
        printf("Error, empty input!\n");
    }
    else if (string[BUF_SIZE - 2] != '\0' && string[BUF_SIZE - 2] != '\n')
    {
        return_code = ERR_BUF;
        printf("Error, buffer overflow!\n");
    }
    else
    {
        char *words[BUF_SIZE / 2];

        int w_amount = split(string, words, " ,;:-.!?\n");
        if (w_amount == 0)
        {
            return_code = ERR_NO_WORDS;
            printf("Error, no words in string!\n");
        }
        else
        {
            char *filtered_words[BUF_SIZE / 2];

            int filtered_count = filter_words_remove(words, w_amount, words[w_amount - 1], filtered_words);

            char joined_string[BUF_SIZE];
            joined_string[0] = '\0';

            if (filtered_count > 0)
            {
                join_reversed_processed(filtered_words, filtered_count, joined_string);
                printf("Result: %s\n", joined_string);
            }
            else
            {
                return_code = ERR_NO_WORDS_PROCESSED;
                printf("Error, empty processed string!\n");
            }
        }
    }

    return return_code;
}

char *join_reversed_processed(char **words, int w_count, char *destination)
{
    for (int i = w_count - 1; i > 0; i--)
    {
        strcat(destination, remove_symbol_occures_skip_n(words[i], words[i][0], 1));
        strcat(destination, " ");
    }

    strcat(destination, remove_symbol_occures_skip_n(words[0], words[0][0], 1));
    return destination;
}

