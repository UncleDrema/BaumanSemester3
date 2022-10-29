//
// Created by archdrema on 10/28/22.
//

#ifndef __MATRIX_H
#define __MATRIX_H

#include <stddef.h>
#include "errors.h"

typedef struct sparse_matrix_t {
    /// Количество ненулевых элементов
    size_t el_count;
    /// Количество строк
    size_t rows_count;
    /// Количество столбцов
    size_t cols_count;
    /// Массив индексов массива строк ненулевых элементов, с которых начинается каждый столбец матрицы. (JA)
    size_t *col_p;
    /// Массив номеров строк ненулевых элементов (IA)
    size_t *row_i;
    /// Массив ненулевых элементов (A)
    int *values;
} sparse_matrix_t;

/// Выделить память под обычную матрицу
int **matrix_alloc(size_t n, size_t m);

/// Выделить память под разреженную матрицу
err_t sparse_matrix_alloc(sparse_matrix_t *mat);

/// Преобразовать обычную матрицу в разреженную
err_t matrix_to_sparse(int **data, size_t n, size_t m, size_t el_count, sparse_matrix_t *mat);

/// Освободить память под разреженную матрицу
void free_sparse_matrix(sparse_matrix_t *mat);

/// Обнулить матрицу
void reset_matrix(int **data, size_t n, size_t m);

/// Сложить матрицы обычным способом
err_t matrix_sum(int **a, int **b, int **c, size_t c_n, size_t c_m);

/// Выделить матрицу под результат сложения
err_t sum_sparse_matrix_alloc(sparse_matrix_t *matrix1, sparse_matrix_t *matrix2, sparse_matrix_t *result);

/// Сложить разреженные матрицы
void sparse_matrix_sum(sparse_matrix_t *matrix1, sparse_matrix_t *matrix2, sparse_matrix_t *result);

#endif
