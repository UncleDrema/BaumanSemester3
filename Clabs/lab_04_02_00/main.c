#include <stdio.h>
#include "string_utils.h"
#define BUF_SIZE 258
#define ERR_NO_WORDS 1
#define ERR_EOF 2
#define ERR_BUF 3
#define OK 0

void transform(char **matrix, char *buf, int n, int m);
void count_unique_words_to_arr(char **words, int w_count, char **unique_words, int uw_count, int *u_c_arr);

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
        char *words[BUF_SIZE / 2], buf[BUF_SIZE / 2][BUF_SIZE];
        transform(words, (char *)buf, BUF_SIZE / 2, BUF_SIZE);

        int w_amount = split(string, words, " ,;:-.!?\n");
        if (w_amount == 0)
        {
            return_code = ERR_NO_WORDS;
            printf("Error, no words in string!\n");
        }
        else
        {
            char *unique_words[BUF_SIZE / 2], unique_buf[BUF_SIZE / 2][BUF_SIZE];
            transform(unique_words, (char *)unique_buf, BUF_SIZE / 2, BUF_SIZE);

            int unique_count = get_unique_words(words, w_amount, unique_words);
            int str_amounts[BUF_SIZE / 2];

            count_unique_words_to_arr(words, w_amount, unique_words, unique_count, str_amounts);

            printf("Result: \n");
            for (int i = 0; i < unique_count; i++)
            {
                printf("%s %d\n", unique_words[i], str_amounts[i]);
            }
        }
    }

    return return_code;
}

void count_unique_words_to_arr(char **words, int w_count, char **unique_words, int uw_count, int *u_c_arr)
{
    for (int i = 0; i < uw_count; i++)
    {
        u_c_arr[i] = count_str_in_str_arr(words, w_count, unique_words[i]);
    }
}

void transform(char **matrix, char *buf, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        matrix[i] = buf + i * m;
    }
}
