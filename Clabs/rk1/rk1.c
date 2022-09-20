#include <stdio.h>
#define OK 0
#define INP_ERR -1
#define ERR_IO 1
#define ERR_SIZE 2
#define N 10

int input_array(int *arr, int len);
void print_array(int *arr, int len);
void group_array(int *arr, int len);
void swap(int *a, int *b);

// Вариант 1 (нули, отрицательные, положительные)
int main(void)
{
    int arr[N], return_code = OK, n;
    if (scanf("%d", &n) != 1)
    {
        printf("Input error!\n");
        return_code = ERR_IO;
    }
    else if (n < 1 || n > N)
    {
        printf("N must be from one to ten!\n");
        return_code = ERR_SIZE;
    }
    else if (input_array(arr, n) != OK)
    {
        printf("Input error!\n");
        return_code = ERR_IO;
    }
    else
    {
        printf("Your array: ");
        print_array(arr, n);
        printf("Grouped array: ");
        group_array(arr, n);
        print_array(arr, n);
    }

    return return_code;
}

void group_array(int *arr, int len)
{
    int counter = 0;

    // All zeros
    for (int i = counter; i < len; i++)
    {
        if (arr[i] == 0)
        {
            for (int j = i; j > counter; j--)
            {
                swap(arr + j - 1, arr + j);
            }
            counter++;
        }
    }

    // All negative
    for (int i = counter; i < len; i++)
    {
        if (arr[i] < 0)
        {
            for (int j = i; j > counter; j--)
            {
                swap(arr + j - 1, arr + j);
            }
            counter++;
        }
    }
    
    // All positive
    for (int i = counter; i < len; i++)
    {
        if (arr[i] > 0)
        {
            for (int j = i; j > counter; j--)
            {
                swap(arr + j - 1, arr + j);
            }
            counter++;
        }
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int input_array(int *arr, int len)
{
    int state = OK;
    for (int i = 0; (i < len) && ((state = (scanf("%d", arr + i)) == 1 ? OK : INP_ERR) == OK); i++);
    return state;
}

void print_array(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d", arr[i]);
        if (i != len - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
}
