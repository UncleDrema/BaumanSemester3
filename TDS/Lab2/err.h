//
// Created by archdrema on 9/24/22.
//

#ifndef __ERR_H
#define __ERR_H

/// Коды ошибок
typedef enum
{
    /// Ошибки нет
    OK = 0,
    /// Ошибка ввода-вывода
    IO_ERROR = 1,
    /// Ошибка аргументов функции
    ARGS_ERR = 2,
    /// Больше нет данных
    NO_MORE_DATA = 3
} err_t;

#endif
