//
// Created by archdrema on 10/28/22.
//

#include "errors.h"
#include <stdio.h>

void output_error(err_t error)
{
    switch (error)
    {
        case ERROR_MEMORY:
            printf("Error: memory.\n");
            break;
        case ERROR_SIZE:
            printf("Error: incorrect matrix size.\n");
            break;
        case ERROR_READING_FILE:
            printf("Error while reading file.\n");
            break;
        case ERROR_COMMAND_LINE:
            printf("Error: incorrect command line.\n");
            break;
        case ERROR_OPENING_FILE:
            printf("Error: openning file.\n");
            break;
        case ERROR_COMMAND:
            printf("Error: unknown command.\n");
            break;
        case ERROR_INCORRECT_NUMBER:
            printf("Error: incorrect number.\n");
            break;
        case ERROR_INCORRECT_SYMBOL:
            printf("Error: incorrect symbol.\n");
            break;
        case ERROR_LINE_LENGTH:
            printf("Error: wrong line size.\n");
            break;
        default:
            break;
    }
}

