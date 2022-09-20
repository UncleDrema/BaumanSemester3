//
// Created by archdrema on 9/11/22.
//

#ifndef __UTILS_H
#define __UTILS_H
#define TO_DIGIT(ch) ((ch) - '0')

#include "err.h"

/**
 * Переводит строковое представление целого числа в число (может кидать ошибку NOT_A_NUMBER при неудаче)
 * @param str строка входа
 * @return численное представление строки
 */
FUNC(int, err_string_to_int, char *str);

/**
 * Пропускает символы до следующей строки или до EOF
 * @param f обрабатываемый поток
 * @return число пропущенных символов
 */
int skip_to_nl(FILE *f);

#endif
