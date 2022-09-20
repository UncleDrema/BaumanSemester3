#include <stdio.h>
#define ERR_OVERLOAD 0
#define ERR_IO 2
#define ERR_INVALID 1

int fib(int, unsigned int*);

int main()
{
    int n, return_code = 0;
    printf("Input N: ");

    if (!scanf("%d", &n))
    {   
        printf("Invalid input, N has to be an integer!\n"); 
        return_code = ERR_IO;
    }
    else if (n < 0)
    {
        printf("N cannot be lower than zero!\n");
        return_code = ERR_INVALID;
    }
    else
    {
        unsigned int fibonacci_num;

        if (fib(n, &fibonacci_num))
        {
            printf("Fib[n] is %u\n", fibonacci_num);
        }
        else
        {
            printf("Integer overload occured! Cannot return Fib[n]\n");
            return_code = ERR_INVALID;
        }
    }

    return return_code;
}

int fib(int n, unsigned int*result)
{
    int return_code = 1;
    unsigned int n_prev = 0, n_curr = 1, temp;
    if (n == 0)
        n_curr = 0;
    else
    {
        while (--n && (n_curr >= n_prev))
        {
            temp = n_prev + n_curr;
            n_prev = n_curr;
            n_curr = temp;
        }

        if (n_curr < n_prev)
            return_code = ERR_OVERLOAD;
    }

    *result = n_curr;

    return return_code;
}
