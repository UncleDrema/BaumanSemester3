// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
//
// Created by archdrema on 10/17/22.
//

#include <matrix_io.h>
#include <utils.h>

err_t input_coordinate_form(FILE *f, matrix_t *matrix)
{
    if (matrix == NULL)
    {
        return DATA_ERR;
    }

    size_t rows, cols, nonnull;
    if (fscanf(f, "%zu%zu%zu", &rows, &cols, &nonnull) != 3)
    {
        return IO_ERR;
    }

    if (alloc_matrix(matrix, rows, cols) != OK)
    {
        return MEMORY_ERR;
    }

    if (skip_to_nl(f) != 1)
    {
        return IO_ERR;
    }

    // init matrix with zero
    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = 0.0f;
        }
    }

    for (size_t i = 0; i < nonnull; i++)
    {
        size_t row, col;
        float value;
        if (fscanf(f, "%zu %zu %f", &row, &col, &value) != 3)
        {
            return IO_ERR;
        }

        if (skip_to_nl(f) != 1)
        {
            return IO_ERR;
        }

        row--;
        col--;
        if (row >= matrix->rows || col >= matrix->cols)
        {
            return DATA_ERR;
        }

        matrix->data[row][col] = value;
    }

    return OK;
}

err_t print_simple_format(FILE *f, matrix_t *matrix)
{
    if (matrix == NULL || matrix->cols == 0 || matrix->rows == 0)
    {
        return DATA_ERR;
    }

    fprintf(f, "%zu %zu\n", matrix->rows, matrix->cols);
    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            if (j == matrix->cols - 1)
            {
                fprintf(f, "%.6f\n", matrix->data[i][j]);
            }
            else
            {
                fprintf(f, "%.6f ", matrix->data[i][j]);
            }
        }
    }

    return OK;
}