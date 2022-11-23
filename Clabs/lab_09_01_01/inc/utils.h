//
// Created by archdrema on 10/28/22.
// Описание вспомогательных функций

#ifndef __UTILS_H
#define __UTILS_H
#define TO_DIGIT(ch) ((ch) - '0')

#include "err.h"

/**
 * Переводит строковое представление целого числа в число (может кидать ошибку NOT_A_NUMBER при неудаче)
 * @param str in строка входа
 * @param res out численное представление строки
 * @return код ошибки
 */
err_t string_to_int(char *str, int *res);

/**
 * Пропускает символы до следующей строки или до EOF
 * @param f обрабатываемый поток
 * @return число пропущенных символов
 */
int skip_to_nl(FILE *f);

#endif
