//
// Created by archdrema on 9/25/22.
// Заголовочный файл с определением макроса безопасного освобождения динамической памяти

#ifndef __SAFE_FREE_H
#define __SAFE_FREE_H
#include <stdlib.h>

/// Безопасное освобождение динамической памяти с обнулением указателя
#define SAFE_FREE(p) free(p); p = NULL

#endif
