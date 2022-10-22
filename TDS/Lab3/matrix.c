//
// Created by archdrema on 10/22/22.
//

#include "matrix.h"

err_t alloc_sparse_matrix(sparse_matrix_t *m, size_t rows, size_t cols, size_t elements)
{
    if (m == NULL || rows == 0 || cols == 0)
    {
        return DATA_ERR;
    }

    m->rows = rows;
    m->cols = cols;
    m->non_null = elements;
    m->a = calloc(elements, sizeof(int));
    if (m->a == NULL)
    {
        return MEMORY_ERR;
    }

    m->ia = calloc(elements, sizeof(size_t));
    if (m->ia == NULL)
    {
        return MEMORY_ERR;
    }

    return OK;
}

static void free_ja_list(struct ja_struct *list)
{
    if (list == NULL)
    {
        return;
    }

    free_ja_list(list->next);
    free(list);
}

void free_sparse_matrix(sparse_matrix_t *m)
{
    free(m->a);
    free(m->ia);
    free_ja_list(m->ja);
}

err_t sparse_matrix_add(sparse_matrix_t *a, sparse_matrix_t *b, sparse_matrix_t *res)
{
    if (a == NULL || b == NULL || res == NULL || a->rows != b->rows || a->cols != b->cols
        || (a->non_null + b->non_null) < a->non_null
        || (a->non_null + b->non_null) < b->non_null)
    {
        return DATA_ERR;
    }

    size_t total_els = 0;

    struct ja_struct *a_col = a->ja, *b_col = b->ja;

    alloc_sparse_matrix(res, a->rows, a->cols, a->non_null + b->non_null);

    size_t a_col_n = 0, b_col_n = 0;

    while (a_col != NULL && b_col != NULL)
    {
        if (a_col != NULL)
        {
            a_col_n = a_col->n;
            a_col = a_col->next;
        }

        if (b_col != NULL)
        {
            b_col_n = b_col->n;
            b_col = b_col->next;
        }
    }

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

err_t alloc_matrix(matrix_t *m, size_t rows, size_t cols)
{
    if (m == NULL || rows == 0 || cols == 0)
    {
        return DATA_ERR;
    }

    m->rows = 0;
    m->cols = 0;
    m->data = NULL;

    int **data = calloc(rows, sizeof(int *));
    if (data == NULL)
    {
        return MEMORY_ERR;
    }

    size_t i = 0;
    int *temp;
    err_t err = OK;
    for (; i < rows && err == OK; i++)
    {
        temp = calloc(cols, sizeof(int));
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

void free_matrix(matrix_t *m)
{
    if (m == NULL || m->rows == 0 || m->cols == 0)
    {
        return;
    }
    for (size_t i = 0; i < m->rows; i++)
    {
        free(m->data[i]);
    }
    free(m->data);
    m->data = NULL;
}