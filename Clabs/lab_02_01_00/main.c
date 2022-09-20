#include <stdio.h>
#define ERR_IO 1
#define ERR_INVALID 2
#define ERR_NO_EVEN 3
#define NO_EVEN_IN_ARR -1
#define INP_ERR -1
#define OK 0
#define N 10


int input_array(int *arr, int n);
int sum_of_even(int *arr, int n, int *result);

int main(void)
{
    int return_code = OK, arr[N], n;

    printf("%s", "Please, input n: ");
    if (scanf("%d", &n) != 1)
    {
        printf("%s", "Error, n must be an integer!\n");
        return_code = ERR_IO;
    }
    else if (n < 1 || n > N)
    {
        printf("%s", "Error, n must be from one to ten!\n");
        return_code = ERR_INVALID;
    }
    else if (input_array(arr, n) != OK)
    {
        printf("%s", "Error, element must be an integer!\n");
        return_code = ERR_INVALID;
    }
    else
    {
        int sum = 0;
        if (sum_of_even(arr, n, &sum) != OK)
        {
            printf("%s", "Error, no even elements in array!\n");
            return_code = ERR_NO_EVEN;
        }
        else
        {
            printf("Sum of even elements: %d\n", sum);
        }
    }

    return return_code;
}

int sum_of_even(int *arr, int n, int *result)
{
    int return_code = OK, even_count = 0;
    for (int i = 0; i < n; i++)
    {
        int cur = arr[i];
        if (cur % 2 == 0)
        {
            even_count++;
            *result += cur;
        }
    }

    if (even_count < 1)
    {
        return_code = NO_EVEN_IN_ARR;
    }

    return return_code;
}

int input_array(int *arr, int n)
{
    int return_code = OK;
    printf("%s", "Please, input array elements: ");
    for (int i = 0; i < n && (return_code = ((scanf("%d", arr + i) == 1) ? OK : INP_ERR)) == OK; i++);
    return return_code;
}
