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

    return 0;
}