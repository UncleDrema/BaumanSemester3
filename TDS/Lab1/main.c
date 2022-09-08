// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <stdio.h>
#include "number.h"
#include "utils.h"

int main() {
    real_t in_num = {{0, {[0] = 0}}, {0, {[0] = 0}}};

    err_t errcode = input_num(stdin, &in_num);
    if (errcode == OK)
    {
        print_real(stdout, &in_num);
    }
    else
    {
        printf("Error #%d", errcode);
    }

    return errcode;
}