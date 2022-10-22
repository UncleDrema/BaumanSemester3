//
// Created by archdrema on 10/17/22.
//

#ifndef __MATRIX_IO_H
#define __MATRIX_IO_H

#include <err.h>
#include <stdio.h>
#include <matrix.h>

/**
 * Ввод матрицы в координатном виде
 * @param f поток ввода
 * @param matrix указатель на вводимую матрицу
 * @return код ошибки
 */
err_t input_coordinate_form(FILE *f, matrix_t *matrix);

/**
 * Вывод матрицы в обычном виде
 * @param f поток вывода
 * @param matrix указатель на выводимую матрицу
 * @return код ошибки
 */
err_t print_simple_format(FILE *f, matrix_t *matrix);

#endif
