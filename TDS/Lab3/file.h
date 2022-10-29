//
// Created by archdrema on 10/28/22.
//

#ifndef __FILE_H
#define __FILE_H

#include <stdbool.h>
#include <stdio.h>
#include "matrix.h"

/// Ввести матрицо
int matrix_read(FILE *f, int **data, size_t nnz, size_t n, size_t m, bool print);

/// Выделить память под матрицу
int matrix_create(FILE *f, int ***data, size_t *n, size_t *m, size_t *el_count, bool print);

/// Вывести матрицу
void matrix_output(FILE *f, int **data, size_t n, size_t m);

/// Вывести разреженную матрицу
void sparse_output(FILE *f, sparse_matrix_t *csr);

/// Прочитаь поток ввода до новой строки
int skip_to_nl(FILE *f);

#endif
