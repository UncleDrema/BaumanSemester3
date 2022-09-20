#include "num_utils.h"
#include <string.h>
#include <stdlib.h>

size_t numlen(int number)
{
    size_t len = 0;
    do
    {
        len++;
        number /= 10;
    } while (number != 0);
    return len;
}

int to_number_safe(char *str, int *number)
{
    *number = atoi(str);

    return strlen(str) == numlen(*number);
}

int rand_range(int low, int high)
{
    return rand() % (high - low + 1) + low;
}
