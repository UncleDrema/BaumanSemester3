//
// Created by archdrema on 10/28/22.
//

#ifndef __ERRORS_H
#define __ERRORS_H

typedef enum err_t
{
    OK = 0,
    ERROR_MEMORY = 1,
    ERROR_SIZE = 2,
    ERROR_READING_FILE = 3,
    ERROR_COMMAND_LINE = 4,
    ERROR_OPENING_FILE = 5,
    ERROR_COMMAND = 6,
    ERROR_INCORRECT_NUMBER = 7,
    ERROR_INCORRECT_SYMBOL = 8,
    ERROR_LINE_LENGTH = 9
} err_t;

void output_error(err_t error);

#endif
