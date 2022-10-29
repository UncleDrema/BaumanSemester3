//
// Created by archdrema on 10/28/22.
//

#ifndef __IO_H
#define __IO_H

#include "matrix.h"

void menu();

void output_num_center(size_t x, int number);

void output_llu_num_center(long long unsigned x, int number);

void output_add_result(long long unsigned csr_time, long long unsigned matrix, sparse_matrix_t *csr);

int input_number(int *x);

#endif
