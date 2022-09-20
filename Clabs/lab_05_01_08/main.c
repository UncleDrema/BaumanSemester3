#include <stdio.h>
#include "process.h"
#define OK 0

int main(void)
{
    int return_code = OK, dist;

    switch (process(stdin, &dist))
    {
        case OK:
            printf("Minimum distance between local maximums is: %d\n", dist);
            break;
        case ERR_NOT_ENOUGH_DATA:
        case ERR_NOT_ENOUGH_LOC_MAX:
            printf("There was not enought data in input!");
            return_code = 1;
            break;
    }

    return return_code;
}
