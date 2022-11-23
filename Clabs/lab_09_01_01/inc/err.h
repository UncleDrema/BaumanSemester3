//
// Created by archdrema on 10/28.22.
// Описание кодов ошибки

#ifndef __ERR_H
#define __ERR_H
#include <stdio.h>

/**
 * Тип ошибки
 */
typedef int err_t;

/**
 * Отсутствие ошибки
 */
typedef enum
{
    OK = 0
} no_err_t;

/**
 * Ошибки ввода/вывода
 */
typedef enum
{
    OPEN_ERR = 1,
    CLOSE_ERR = 2
} io_err_t;

/**
 * Ошибки аргументов командной строки
 */
typedef enum
{
    NOT_ENOUGH_ARGS = 3,
    TOO_MUCH_ARGS = 4,
} args_err_t;

/**
 * Ошибки утилитарных функций
 */
typedef enum
{
    NOT_A_NUMBER = 5
} utils_err_t;

/**
 * Ошибки, связанные с работой программы по задаче
 */
typedef enum
{
    WRONG_FIELD = 6,
    FILM_WRONG_FORMAT = 7,
    INPUT_END = 8,
    NOT_FOUND = 9,
    WRONG_DATA = 10
} task_err_t;

/**
 * Ошибки памяти
 */
typedef enum
{
    ALLOC_ERR = 12
} memory_err_t;

#endif
