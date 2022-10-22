//
// Created by archdrema on 10/22/22.
//

#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H

#include <stddef.h>
#include "err.h"
#include <stdlib.h>

/// Структура для хранения матрицы
typedef struct
{
    /// Непосредственно данные в матрице
    int **data;
    /// Количество строк
    size_t rows;
    /// Количество столбцов
    size_t cols;
} matrix_t;

/// Структура для хранения разреженной матрицы
typedef struct {
    size_t rows;
    size_t cols;
    size_t non_null;
    int *a;
    size_t *ia;
    struct ja_struct {
        size_t n;
        struct ja_struct *next;
    } *ja;
} sparse_matrix_t;

err_t alloc_matrix(matrix_t *m, size_t rows, size_t cols);

err_t matrix_add(matrix_t *a, matrix_t *b, matrix_t *res);

err_t alloc_sparse_matrix(sparse_matrix_t *m, size_t rows, size_t cols, size_t elements);

err_t sparse_matrix_add(sparse_matrix_t *a, sparse_matrix_t *b, sparse_matrix_t *res);

void free_sparse_matrix(sparse_matrix_t *m);

void free_matrix(matrix_t *m);

#endif //LAB3_MATRIX_H
