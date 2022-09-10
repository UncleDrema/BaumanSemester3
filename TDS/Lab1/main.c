// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <stdio.h>
#include "number.h"
#include "utils.h"

int main() {
    real_input_t in_integer = ZERO_NUMBER;
    real_input_t in_real = ZERO_NUMBER;

#ifndef DEBUG
    printf("Please, input integer number with <= 30 digits\n");
    printf("±------------------------------\n");
#endif
    err_t errcode = input_integer_num(stdin, &in_integer);

    if (errcode == OK)
    {
#ifndef DEBUG
        printf("Please, input real number in format: ±m.n E ±K, where m+n total length <= 30 digits and K length <= 5 digits\n");
        printf("±----.----.----.----.----.----.----.-- E ±-----\n");
#endif
        errcode = input_real_num(stdin, &in_real);

        if (errcode == OK)
        {
            real_inner_t inner_integer = ZERO_NUMBER;
            real_inner_t inner_real = ZERO_NUMBER;

            input_to_inner(&in_integer, &inner_integer);
            input_to_inner(&in_real, &inner_real);

            real_inner_t delim_result = ZERO_NUMBER;
            errcode = divide_inner_t(&inner_integer, &inner_real, &delim_result);
            if (errcode == OK)
            {
#ifndef DEBUG
                printf("Division result:\n");
#endif
                real_t finalResult;
                errcode = inner_to_real(&delim_result, &finalResult);

                if (errcode == OK)
                {
                    print_real(stdout, &finalResult);
                    puts("");
                }
            }
        }
    }

    if (errcode != OK)
    {
        printf("Error: ");
        print_err_t(errcode);
        puts("");
    }

    return errcode;
}