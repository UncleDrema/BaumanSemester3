// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
//
// Created by archdrema on 10/9/22.
//

#include <matrix.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>
#include <stdio.h>

err_t alloc_matrix(matrix_t *m, size_t rows, size_t cols)
{
    if (m == NULL || rows == 0 || cols == 0)
    {
        return DATA_ERR;
    }

    m->rows = 0;
    m->cols = 0;
    m->data = NULL;

    float **data = calloc(rows, sizeof(float *));
    if (data == NULL)
    {
        return MEMORY_ERR;
    }

    size_t i = 0;
    float *temp;
    err_t err = OK;
    for (; i < rows && err == OK; i++)
    {
        temp = calloc(cols, sizeof(float));
        if (temp == NULL)
        {
            err = MEMORY_ERR;
            // cancel i++ and set i to previous, "OK" row
            i -= 2;
        }
        else
        {
            data[i] = temp;
        }
    }

    // free already allocated memory
    if (err != OK)
    {
        for (; i > 0; i--)
        {
            free(data[i]);
        }
        free(data);
    }
    else
    {
        m->rows = rows;
        m->cols = cols;
        m->data = data;
    }

    return err;
}

err_t free_matrix(matrix_t *m)
{
    if (m == NULL)
    {
        return OK;
    }

    if (m->rows == 0 || m->cols == 0)
    {
        return DATA_ERR;
    }

    for (size_t i = 0; i < m->rows; i++)
    {
        free(m->data[i]);
    }
    free(m->data);
    m->data = NULL;
    return OK;
}

err_t matrix_add(matrix_t *a, matrix_t *b, matrix_t *res)
{
    if (res == NULL || a == NULL || b == NULL || a->rows != b->rows || a->cols != b->cols)
    {
        return DATA_ERR;
    }

    size_t rows = a->rows, cols = a->cols;
    err_t err = alloc_matrix(res, rows, cols);
    if (err != OK)
    {
        return MEMORY_ERR;
    }

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            res->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }

    return OK;
}

err_t matrix_mul(matrix_t *a, matrix_t *b, matrix_t *res)
{
    if (res == NULL || a == NULL || b == NULL || a->cols != b->rows)
    {
        return DATA_ERR;
    }

    size_t rows = a->rows, cols = b->cols, p = a->cols;
    err_t err = alloc_matrix(res, rows, cols);
    if (err != OK)
    {
        return MEMORY_ERR;
    }

    float temp;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            temp = 0;
            for (size_t k = 0; k < p; k++)
            {
                temp += a->data[i][k] * b->data[k][j];
            }

            res->data[i][j] = temp;
        }
    }

    return OK;
}

/**
 * Скопировать матрицу в новую переменную
 * @param from матрица, которая копируется
 * @param to матрица, куда копируется
 * @return код ошибки
 */
static err_t matrix_copy(matrix_t *from, matrix_t *to)
{
    if (from == NULL)
    {
        return DATA_ERR;
    }

    err_t err = alloc_matrix(to, from->rows, from->cols);
    if (err != OK)
    {
        return MEMORY_ERR;
    }

    for (size_t i = 0; i < from->rows; i++)
    {
        memcpy(to->data[i], from->data[i], sizeof(float) * to->cols);
    }

    return OK;
}

/**
 * Получить доп. минор к элементу M0n
 * @param m матрица, для которой получается минор
 * @param n номер столбца элемента, по кторому берётся минор
 * @param min указатель на переменную для сохранения минора
 * @return код ошибки
 */
static err_t get_minor(matrix_t *m, size_t n, matrix_t *min)
{
    if (m == NULL || n >= m->cols || m->cols != m->rows || m->rows == 1)
    {
        return DATA_ERR;
    }

    size_t size = m->rows - 1;

    err_t rc = alloc_matrix(min, size, size);
    if (rc != OK)
    {
        return MEMORY_ERR;
    }

    /*
     * 0,0 0,1 0,2
     * 1,0 1,1 1,2
     * 2,0 2,1 2,2
     *
     * Минор n = 1:
     * 1,0 1,2
     * 2,0 2,2
     *
     * Копируем для строк с 1 до кол-ва строк
     * элементы от начала до n - 1
     * и элементы от n + 1 до конца
     */

    /*
     * 0,0 0,1 0,2 0,3
     * 1,0 1,1 1,2 1,3
     * 2,0 2,1 2,2 2,3
     * 3,0 3,1 3,2 3,3
     *
     * Минор n = 2, size = 3
     * 1,0 1,1 1,3
     * 2,0 2,1 2,3
     * 3,0 3,1 3,3
     *
     * Минор n = 0
     * 1,1 1,2 1,3
     * 2,1 2,2 2,3
     * 3,1 3,2 3,3
     */

    for (size_t i = 1; i < m->rows; i++)
    {
        memcpy(min->data[i - 1], m->data[i], n * sizeof(float));
        memcpy(min->data[i - 1] + n, m->data[i] + n + 1, (size - n) * sizeof(float));
    }

    return OK;
}

err_t get_determinant(matrix_t *m, float *det)
{
    if (det == NULL || m == NULL || m->rows != m->cols)
    {
        return DATA_ERR;
    }

    size_t size = m->rows;

    float res = 0;
    if (size == 1)
    {
        res = m->data[0][0];
    }
    else if (size == 2)
    {
        res = m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
    }
    else
    {
        matrix_t min;
        float temp;
        for (size_t i = 0; i < size; i++)
        {
            get_minor(m, i, &min);

            get_determinant(&min, &temp);

            free_matrix(&min);

            res += temp * (m->data[0][i]) * (float)((1 + (1 + i)) % 2 == 0 ? 1 : -1);
        }
    }

    *det = res;
    return OK;
}

/// Поделить строку матрицы на число
static void div_row(matrix_t *m, size_t row, float divider)
{
    for (size_t i = 0; i < m->cols; i++)
    {
        m->data[row][i] /= divider;
    }
}

/// Добавить к матрице другую строку матрицы с заданным множителем
static void add_row(matrix_t *m, size_t from, size_t to, float mul)
{
    for (size_t i = 0; i < m->cols; i++)
    {
        m->data[to][i] += mul * m->data[from][i];
    }
}

err_t matrix_rev(matrix_t *m, matrix_t *res)
{
    if (res == NULL || m == NULL || m->rows != m->cols)
    {
        return DATA_ERR;
    }

    float det;
    err_t rc = get_determinant(m, &det);
    if (rc != OK)
    {
        return rc;
    }

    if (float_eq(det, 0.0f, 1e-6f))
    {
        return ZERO_DET_ERR;
    }

    size_t size = m->rows;
    matrix_t matr;

    rc = matrix_copy(m, &matr);
    if (rc != OK)
    {
        return rc;
    }

    rc = alloc_matrix(res, size, size);
    if (rc != OK)
    {
        return rc;
    }

    // make an eye matrix
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            res->data[i][j] = i == j ? 1 : 0;
        }
    }

    float temp;
    for (size_t i = 0; i < size; i++)
    {
        temp = matr.data[i][i];
        div_row(&matr, i, temp);
        div_row(res, i, temp);

        for (size_t j = 0; j < size; j++)
        {
            if (j == i)
            {
                continue;
            }

            temp = matr.data[j][i];
            add_row(&matr, i, j, -temp);
            add_row(res, i, j, -temp);
        }
    }

    free_matrix(&matr);
    return OK;
}