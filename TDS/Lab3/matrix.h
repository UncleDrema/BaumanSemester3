//
// Created by archdrema on 10/28/22.
//

#ifndef __MATRIX_H
#define __MATRIX_H

#include <stddef.h>
#include "errors.h"

typedef struct sparse_matrix_t {
    size_t el_count;
    size_t rows_count;
    size_t cols_count;
    size_t *col_p;
    size_t *row_i;
    int *values;
} sparse_matrix_t ;

int **matrix_alloc(size_t n, size_t m);

err_t sparse_matrix_alloc(sparse_matrix_t *mat);

err_t matrix_to_sparse(int **data, size_t n, size_t m, size_t el_count, sparse_matrix_t *mat);

void free_sparse_matrix(sparse_matrix_t *mat);

void reset_matrix(int **data, size_t n, size_t m);

err_t matrix_sum(int **a, int **b, int **c, size_t c_n, size_t c_m);

err_t sum_sparse_matrix_alloc(sparse_matrix_t *matrix1, sparse_matrix_t *matrix2, sparse_matrix_t *result);

void sparse_matrix_sum(sparse_matrix_t *matrix1, sparse_matrix_t *matrix2, sparse_matrix_t *result);

#endif
