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
 * Пропускает символы до следующей строки или до EOF
 * @param f обрабатываемый поток
 * @return число пропущенных символов
 */
int skip_to_nl(FILE *f);

#endif