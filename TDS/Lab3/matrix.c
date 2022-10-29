//
// Created by archdrema on 10/28/22.
//

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "errors.h"
#include "file.h"
#include "matrix.h"


int **matrix_alloc(size_t n, size_t m)
{
    int **data = malloc(n * sizeof(int *) + n * m * sizeof(int));
    if (!data)
    {
        return NULL;
    }
    for (size_t i = 0; i < n; i++)
    {
        data[i] = (int *) ((char *)data + n * sizeof(int *) + i * m * sizeof(int));
    }

    return data;
}

err_t sparse_matrix_alloc(sparse_matrix_t *mat)
{
    mat->values = calloc(mat->el_count, sizeof(int));
    if (!mat->values)
    {
        return ERROR_MEMORY;
    }

    mat->row_i = calloc(mat->el_count, sizeof(size_t));
    if (!mat->row_i)
    {
        free(mat->values);
        return ERROR_MEMORY;
    }

    mat->col_p = calloc((mat->cols_count + 1), sizeof(size_t));
    if (!mat->col_p)
    {
        free(mat->values);
        free(mat->row_i);
        return ERROR_MEMORY;
    }

    return OK;
}

err_t matrix_to_sparse(int **data, size_t n, size_t m, size_t el_count, sparse_matrix_t *mat)
{
    mat->rows_count = n;
    mat->cols_count = m;
    mat->el_count = el_count;
    err_t rc = sparse_matrix_alloc(mat);
    if (rc != OK)
    {
        return rc;
    }

    size_t values_elems = 0;
    for (size_t j = 0; j < m; j++)
    {
        mat->col_p[j] = values_elems;
        for (size_t i = 0; i < n; i++)
        {
            if (data[i][j] != 0)
            {
                mat->row_i[values_elems] = i;
                mat->values[values_elems] = data[i][j];
                values_elems++;
            }
        }
    }
    mat->col_p[m] = values_elems;

    return rc;
}

void free_sparse_matrix(sparse_matrix_t *mat)
{
    free(mat->col_p);
    free(mat->row_i);
    free(mat->values);
}

void reset_matrix(int **data, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            data[i][j] = 0;
        }
    }
}

err_t matrix_sum(int **a, int **b, int **c, size_t c_n, size_t c_m)
{
    for (size_t i = 0; i < c_n; i++)
    {
        for (size_t j = 0; j < c_m; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    return OK;
}

// Выделить матрицу, подсчитав число ненулевых элементов
err_t sum_sparse_matrix_alloc(sparse_matrix_t *matrix1, sparse_matrix_t *matrix2, sparse_matrix_t *result)
{
    if (matrix1->rows_count != matrix2->rows_count || matrix1->cols_count != matrix2->cols_count)
    {
        return ERROR_SIZE;
    }
    result->rows_count = matrix1->rows_count;
    result->cols_count = matrix1->cols_count;
    result->el_count = 0;
    for (size_t j = 0; j < matrix1->cols_count; j++)
    {
        size_t row_i1 = matrix1->col_p[j], row_i2 = matrix2->col_p[j];
        while (row_i1 < matrix1->col_p[j + 1] || row_i2 < matrix2->col_p[j + 1])
        {
            if (row_i1 >= matrix1->col_p[j + 1])
            {
                row_i2++;
            }
            else if (row_i2 >= matrix2->col_p[j + 1])
            {
                row_i1++;
            }
            else
            {
                if (matrix1->row_i[row_i1] < matrix2->row_i[row_i2])
                {
                    row_i1++;
                }
                else if (matrix1->row_i[row_i1] > matrix2->row_i[row_i2])
                {
                    row_i2++;
                }
                else
                {
                    row_i1++;
                    row_i2++;
                }

            }
            result->el_count++;
        }
    }

    return sparse_matrix_alloc(result);
}

void sparse_matrix_sum(sparse_matrix_t *matrix1, sparse_matrix_t *matrix2, sparse_matrix_t *result)
{
    size_t el_count = 0;
    for (size_t j = 0; j < matrix1->cols_count; j++)
    {
        result->col_p[j] = el_count;
        size_t row_i1 = matrix1->col_p[j], row_i2 = matrix2->col_p[j];
        while (row_i1 < matrix1->col_p[j + 1] || row_i2 < matrix2->col_p[j + 1])
        {
            if (row_i1 >= matrix1->col_p[j + 1])
            {
                result->row_i[el_count] = matrix2->row_i[row_i2];
                result->values[el_count++] += matrix2->values[row_i2];
                row_i2++;
            }
            else if (row_i2 >= matrix2->col_p[j + 1])
            {
                result->row_i[el_count] = matrix1->row_i[row_i1];
                result->values[el_count++] += matrix1->values[row_i1];
                row_i1++;
            }
            else
            {
                if (matrix1->row_i[row_i1] < matrix2->row_i[row_i2])
                {
                    result->row_i[el_count] = matrix1->row_i[row_i1];
                    result->values[el_count++] += matrix1->values[row_i1];
                    row_i1++;
                }
                else if (matrix1->row_i[row_i1] > matrix2->row_i[row_i2])
                {
                    result->row_i[el_count] = matrix2->row_i[row_i2];
                    result->values[el_count++] += matrix2->values[row_i2];
                    row_i2++;
                }
                else
                {
                    result->row_i[el_count] = matrix2->row_i[row_i2];
                    result->values[el_count] += matrix2->values[row_i2] + matrix1->values[row_i1];
                    if (result->values[el_count])
                    {
                        el_count++;
                    }
                    row_i1++;
                    row_i2++;
                }
            }
        }
    }
}

