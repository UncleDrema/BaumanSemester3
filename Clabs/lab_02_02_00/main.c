#include <stdio.h>
#define OK 0
#define INP_ERR -1
#define ERR_IO 1
#define ERR_INVALID 2
#define ERR_NO_VALID_ELEMENTS 3
#define N 10


int input_array(int *arr, int n);
float calc_average(int *arr, int n);
int copy_more_than(int *from, int n_from, int *to, float value);
void print_array(int *arr, int n);

int main(void)
{
    int return_code = OK, arr[N], n;

    printf("%s", "Please, input n: ");
    if (scanf("%i", &n) != 1)
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
        float mid = calc_average(arr, n);
        int new_arr[N];
        int new_n = copy_more_than(arr, n, new_arr, mid);
        if (new_n == 0)
        {
            printf("%s", "Error, no elements more than mid in array!\n");
            return_code = ERR_NO_VALID_ELEMENTS;
        }
        else
        {
            print_array(new_arr, new_n);
        }
    }

    return return_code;
}

float calc_average(int *arr, int n)
{
    float sum = 0;
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            sum += arr[i];
        }
        sum /= n;
    }

    return sum;
}

int copy_more_than(int *from, int n_from, int *to, float value)
{
    int j = 0;
    for (int i = 0; i < n_from; i++)
    {
        if (from[i] > value)
        {
            to[j] = from[i];
            j++;
        }
    }

    return j;
}

void print_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%i", arr[i]);
        if (i != n - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
}

int input_array(int *arr, int n)
{
    int return_code = OK;
    printf("%s", "Please, input array elements: ");
    for (int i = 0; i < n && (return_code = ((scanf("%d", arr + i) == 1) ? OK : INP_ERR)) == OK; i++);
    return return_code;
}
