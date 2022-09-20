#include <stdio.h>
#define OK 0
#define INP_ERR -1
#define ERR_IO 1
#define ERR_INVALID 2
#define N 10

int input_array(int *pb, int *pe);
long result(int *pb, int *pe);

int main(void)
{
    int return_code = OK, n, arr[N];

    printf("%s", "Please, input n: ");
    if (scanf("%d", &n) != 1)
    {
        printf("%s", "Error, n must be an integer!\n");
        return_code = ERR_IO;
    }
    else if (n < 2 || n > 10)
    {
        printf("%s", "Error, n must be from two to ten!\n");
        return_code = ERR_INVALID;
    }
    else if (input_array(arr, arr + n) != OK)
    {
        printf("%s", "Error, element must be an integer!\n");
        return_code = ERR_INVALID;
    }
    else
    {
        long res = result(arr, arr + n - 1);
        printf("Result: %ld\n", res);
    }

    return return_code;
}

long result(int *pa, int *pe)
{
    long min, cur_mul;
    int prev = *pa;
    pa++;
    int cur = *pa;
    min = prev * cur;
    while (pa < pe)
    {
        prev = cur;
        pa++;
        cur = *pa;
        cur_mul = prev * cur;
        if (cur_mul < min)
        {
            min = cur_mul;
        }
    }
    return min;
}

int input_array(int *pa, int *pe)
{
    int return_code = OK;
    printf("%s", "Please, input array: ");
    while (pa < pe && (return_code = (scanf("%d", pa++) == 1) ? OK : INP_ERR) == OK);

    return return_code;
}
