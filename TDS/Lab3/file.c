#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "errors.h"
#include "matrix.h"
#include "file.h"
#include "io.h"

int matrix_read(FILE *f, int **data, size_t nnz, size_t n, size_t m, bool print)
{
    int x;
    int error_code = OK;
    for (size_t i = 0; i < nnz && !error_code; ++i)
    {
        int pos_i, pos_j;
        if (print)
        {
            puts("Enter element in format: row col value:");
        }
        if (fscanf(f, "%d%d%d", &pos_i, &pos_j, &x) != 3 || pos_i <= 0 || pos_i > n || pos_j <= 0 || pos_j > m)
        {
            error_code = ERROR_INCORRECT_NUMBER;
        }
        else
        {
            data[pos_i - 1][pos_j - 1] = x;
        }

        skip_to_nl(f);
    }

    return error_code;
}

int matrix_create(FILE *f, int ***data, size_t *n, size_t *m, size_t *el_count, bool print)
{
    int error_code = OK;
    int x, y, not_nul_elems;
    if (print)
    {
        printf("Enter rows_count, cols_count, non zero elements count: ");
    }
    if (fscanf(f, "%d%d%d", &x, &y, &not_nul_elems) != 3 || x <= 0 || y <= 0 || not_nul_elems < 0 || not_nul_elems > x * y)
    {
        error_code = ERROR_INCORRECT_NUMBER;
        *n = 0;
        *m = 0;
    }
    else
    {
        *n = x;
        *m = y;
        *el_count = not_nul_elems;
        *data = matrix_alloc(*n, *m);
        if (!*data)
        {
            error_code = ERROR_MEMORY;
        }
        else
        {
            reset_matrix(*data, *n, *m);
            error_code = matrix_read(f, *data, not_nul_elems, *n, *m, print);
        }
    }

    return error_code;
}

void matrix_output(FILE *f, int **data, size_t n, size_t m)
{
    size_t not_nul_elems = 0;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            if (data[i][j] != 0)
            {
                not_nul_elems++;
            }
        }
    }
    fprintf(f, "%zu %zu %zu\n", n, m, not_nul_elems);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            if (data[i][j] != 0)
            {
                fprintf(f, "%zu %zu %d\n", i + 1, j + 1, data[i][j]);
            }
        }
    }
}

void sparse_output(FILE *f, sparse_matrix_t *mat)
{
    fprintf(f, "A = [ ");
    for (size_t i = 0; i < mat->el_count; ++i)
    {
        fprintf(f, "%d ", mat->values[i]);
    }
    fprintf(f, "]\n");
    fprintf(f, "IA = [ ");
    for (size_t i = 0; i < mat->el_count; ++i)
    {
        fprintf(f, "%zu ", mat->row_i[i] + 1);
    }
    fprintf(f, "]\n");
    fprintf(f, "JA = [ ");
    for (size_t i = 0; i < mat->cols_count + 1; ++i)
    {
        fprintf(f, "%zu ", mat->col_p[i] + 1);
    }
    fprintf(f, "]\n");
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