// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/10/22.
//
#include "err.h"
#include <stdio.h>

#ifdef DEBUG
void print_err(err_t err)
{
    switch (err)
    {
        case OK:
            printf("no error!");
            break;
        case OPEN_ERR:
            printf("file open error!");
            break;
        case CLOSE_ERR:
            printf("file close error!");
            break;
        case NOT_ENOUGH_ARGS:
            printf("not enough arguments!");
            break;
        case TOO_MUCH_ARGS:
            printf("too much arguments!");
            break;
        case NOT_A_NUMBER:
            printf("string can not be parsed as number!");
            break;
        case WRONG_FIELD:
            printf("wrong field specified!");
            break;
        case FILM_WRONG_FORMAT:
            printf("film parsing error!");
            break;
        case INPUT_END:
            printf("input ended too soon!");
            break;
        case NOT_FOUND:
            printf("query item not found!");
            break;
        case TOO_MUCH_ENTRIES:
            printf("too much entries in input file!");
            break;
    }
}
#endif