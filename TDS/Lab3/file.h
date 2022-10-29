//
// Created by archdrema on 10/28/22.
//

#ifndef __FILE_H
#define __FILE_H

#include <stdbool.h>
#include <stdio.h>
#include "matrix.h"

int matrix_read(FILE *f, int **data, size_t nnz, size_t n, size_t m, bool print);

int matrix_create(FILE *f, int ***data, size_t *n, size_t *m, size_t *el_count, bool print);

void matrix_output(FILE *f, int **data, size_t n, size_t m);

void sparse_output(FILE *f, sparse_matrix_t *csr);

int skip_to_nl(FILE *f);

#endif
