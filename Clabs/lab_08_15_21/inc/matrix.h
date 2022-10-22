//
// Created by archdrema on 10/9/22.
//

#ifndef __MATRIX_H
#define __MATRIX_H

#include <stddef.h>
#include <err.h>

/// Структура для хранения матрицы
typedef struct
{
    /// Непосредственно данные в матрице
    float **data;
    /// Количество строк
    size_t rows;
    /// Количество столбцов
    size_t cols;
} matrix_t;

/**
 * Выделить память под матрицу
 * @param m указатель на переменную, для которой необходимо выделить память
 * @param rows кол-во строк
 * @param cols кол-во столбцов
 * @return код ошибки
 * @attention в случае отсутствия ошибки происходит выделение памяти под матрицу!
 */
err_t alloc_matrix(matrix_t *m, size_t rows, size_t cols);

/**
 * Осовбодить память, выделенную под матрицу
 * @param m освобождаемая матрица
 * @return код ошибки
 */
err_t free_matrix(matrix_t *m);

/**
 * Сложить две матрицы в результирующую
 * @param a первая матрица
 * @param b вторая матрица
 * @param res результирующая матрица
 * @return код ошибки
 * @attention в случае отсутствия ошибки памяти происходит выделение памяти под результирующую матрицу!
 */
err_t matrix_add(matrix_t *a, matrix_t *b, matrix_t *res);

/**
 * Умножить две матрицы в результирующую
 * @param a первая матрица
 * @param b вторая матрица
 * @param res результирующая матрица
 * @return код ошибки
 * @attention в случае отсутствия ошибки памяти происходит выделение памяти под результирующую матрицу!
 */
err_t matrix_mul(matrix_t *a, matrix_t *b, matrix_t *res);

/**
 * Вычислить обратную матрицу
 * @param m исходная матрица
 * @param res результирующая матрица
 * @return код ошибки
 * @attention в случае отсутствия ошибки памяти происходит выделение памяти под результирующую матрицу!
 */
err_t matrix_rev(matrix_t *m, matrix_t *res);

/**
 * Посчитать определитель матрицы
 * @param m матрица
 * @param det переменная, в которую сохраняется значение определителя
 * @return код ошибки
 */
err_t get_determinant(matrix_t *m, float *det);

#endif
