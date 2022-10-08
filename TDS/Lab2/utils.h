//
// Created by archdrema on 9/11/22.
//

#ifndef __UTILS_H
#define __UTILS_H
#define TO_DIGIT(ch) ((ch) - '0')
#define RANDOM_ELEMENT(arr, size) arr[rand() % size]
#define STAT_ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define SAFE_FREE(ptr) free(ptr); ptr = NULL

#include <stdio.h>
#include <stdlib.h>
#include "err.h"

/**
 * Переводит строковое представление целого числа в число (может кидать ошибку NOT_A_NUMBER при неудаче)
 * @param str строка входа
 * @param out результат
 * @return ошибка
 */
err_t string_to_int(char *str, int *out);

/**
 * Пропускает символы до следующей строки или до EOF
 * @param f обрабатываемый поток
 * @return число пропущенных символов
 */
int skip_to_nl(FILE *f);

/**
 * Скопировать содержимое файла
 * @param from файл, из которого происходит копирование
 * @param to файл, в который происходит копирование
 */
void copy_file(FILE *from, FILE *to);

/// Убрать перенос строки из строки
void remove_nl(char *str);

#endif