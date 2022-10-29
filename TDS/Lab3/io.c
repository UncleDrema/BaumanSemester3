//
// Created by archdrema on 10/28/22.
//

#include "io.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "matrix.h"
#include "errors.h"

#define DIGITS 10

void menu()
{
    printf("\nChoose command:\n");
    printf("1. Print sparse matrices\n");
    printf("2. Print default matrices\n");
    printf("3. Input matrices\n");
    printf("4. Sum matrices and measure\n");
    printf("5. Sum matrices and print result\n");
    printf("0. Exit\n\n");
    printf("Command: ");
}

static void output_row_center(char *row, int number)
{
    int left = (number - strlen(row)) / 2;
    if (left)
    {
        printf("%*c", left, ' ');
    }
    printf("%s", row);
    int right =  number - left - (int)strlen(row);
    if (right)
    {
        printf("%*c", right, ' ');
    }
}


void output_num_center(size_t x, int number)
{
    char line[number];
    sprintf(line, "%zu", x);
    output_row_center(line, number);
}

void output_llu_num_center(long long unsigned x, int number)
{
    char line[number];
    sprintf(line, "%llu", x);
    output_row_center(line, number);
}

void output_sum_result(long long unsigned csr_time, long long unsigned matrix, sparse_matrix_t *csr)
{
    printf("Repeat 1000x:\n");
    printf("---------------------------------------------\n");
    printf("|     Type     |     Time, ms     |Memory, B|\n");
    printf("|--------------+------------------+---------|\n");
    printf("|    sparse    |");
    output_llu_num_center(csr_time, 18);
    printf("|");
    output_num_center((csr->el_count * 2 * sizeof(size_t) + ((csr->cols_count + 1) * sizeof(int))), 9);
    printf("|\n");
    printf("|--------------+------------------+---------|\n");
    printf("|    Default   |");
    output_llu_num_center(matrix, 18);
    printf("|");
    output_num_center((csr->cols_count * csr->rows_count) * sizeof(int), 9);
    printf("|\n");
    printf("---------------------------------------------\n");
}

static void clear_line(char *line)
{
    if (line[strlen(line) - 1] == '\n')
    {
        line[strlen(line) - 1] = '\0';
    }
}

static int check_len(char *line)
{
    return strlen(line) > DIGITS || !strlen(line);
}

static err_t check_line(char *line, bool digit)
{
    for (char *p = line; *p; ++p)
    {
        if ((!isalpha(*p) && !digit && !isspace(*p)) || (!isdigit(*p) && digit))
        {
            return ERROR_INCORRECT_SYMBOL;
        }
    }
    if (check_len(line))
    {
        return ERROR_LINE_LENGTH;
    }

    return OK;
}

static err_t read_line(FILE *f, char *line, bool digit)
{
    if (!fgets(line, DIGITS + 2, f))
    {
        return ERROR_READING_FILE;
    }
    clear_line(line);

    return check_line(line, digit);
}

err_t input_number(int *x)
{
    char tmp[DIGITS + 2];
    err_t error_code = read_line(stdin, tmp, true), counter = 0;
    if (error_code)
    {
        return error_code;
    }
    char *int_max = "2147483647";
    for (char *p = tmp; *p; p++)
    {
        if (!isdigit(*p) && !isspace(*p))
        {
            return ERROR_INCORRECT_NUMBER;
        }
        counter++;
        if (counter == 10 && strcmp(tmp, int_max) > 0)
        {
            return ERROR_INCORRECT_NUMBER;
        }
    }
    if (sscanf(tmp, "%d", x) != 1)
    {
        return ERROR_INCORRECT_NUMBER;
    }

    return error_code;
}

