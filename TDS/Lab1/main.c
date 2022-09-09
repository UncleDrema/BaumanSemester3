// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <stdio.h>
#include "number.h"
#include "utils.h"

int main() {
    real_input_t in_integer = ZERO_NUMBER;
    real_input_t in_real = ZERO_NUMBER;

    err_t errcode = input_integer_num(stdin, &in_integer);

    if (errcode == OK)
    {
        errcode = input_real_num(stdin, &in_real);

        if (errcode == OK)
        {
            real_inner_t inner_integer = ZERO_NUMBER;
            real_inner_t inner_real = ZERO_NUMBER;

            input_to_inner(&in_integer, &inner_integer);
            input_to_inner(&in_real, &inner_real);

#ifdef DEBUG
            printf("Got numbers:\n");
            print_real_inner(stdout, &inner_integer);
            printf("\nAnd\n");
            print_real_inner(stdout, &inner_real);
            printf("\n");
#endif

            real_inner_t delim_result = ZERO_NUMBER;
            errcode = divide_inner_t(&inner_integer, &inner_real, &delim_result);
            if (errcode == OK)
            {
#ifdef DEBUG
                printf("Result:\n");
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