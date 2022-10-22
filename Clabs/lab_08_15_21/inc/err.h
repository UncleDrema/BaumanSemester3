//
// Created by archdrema on 10/9/22.
//

#ifndef __ERR_H
#define __ERR_H

typedef enum
{
    OK = 0,
    ARGS_ERR = 1,
    IO_ERR = 2,
    MEMORY_ERR = 3,
    DATA_ERR = 4,
    ZERO_DET_ERR = 5
} err_t;

#endif
