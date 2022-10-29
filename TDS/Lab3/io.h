//
// Created by archdrema on 10/28/22.
//

#ifndef __IO_H
#define __IO_H

#include "matrix.h"

/// Вывести меню
void menu();

/// Вывести число по центру
void output_num_center(size_t x, int number);

/// Вывести llu число по центру
void output_llu_num_center(long long unsigned x, int number);

/// Вывести результат сложения
void output_sum_result(long long unsigned csr_time, long long unsigned matrix, sparse_matrix_t *csr);

/// Ввести число
err_t input_number(int *x);

#endif
