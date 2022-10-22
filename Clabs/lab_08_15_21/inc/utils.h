//
// Created by archdrema on 10/9/22.
//

#ifndef __UTILS_H
#define __UTILS_H
#include <stdio.h>

/**
 * Сравнивает два вещественных числа с заданной точностью
 * @param a первое число
 * @param b второе число
 * @param tol требуемая точность
 * @return результат сравнения
 */
int float_eq(float a, float b, float tol);

/**
 * Пропускает символы до следующей строки или до EOF
 * @param f обрабатываемый поток
 * @return число пропущенных символов
 */
int skip_to_nl(FILE *f);

#endif
