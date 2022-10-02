//
// Created by archdrema on 9/21/22.
// Заголовочный файл с определением кодов ошибок

#ifndef __ERR_H
#define __ERR_H

typedef enum
{
    OK = 0,
    ERR_NOT_ENOUGH_ARGS = 1,
    ERR_WRONG_ARGS = 2,
    ERR_MEMORY = 3,
    ERR_IO = 4,
    ERR_DATA = 5
} err_t;

#endif
