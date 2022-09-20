#include <stdio.h>
#define OK 0
#define INP_ERR -1
#define ERR_IO 1
#define ERR_SIZE 2
#define ERR_NO_PRIMES 3
#define N 10
#define M 10
#define PRIME 1
#define NOT_PRIME 0

int input_matrix(int **matrix, int rows, int cols);
void print_matrix(int **matrix, int rows, int cols);
void print_array(int *arr, int len);
int fill_arr_with_primes(int **matrix, int rows, int cols, int *arr);
void reverse_array(int *arr, int len);
void replace_primes(int **matrix, int rows, int cols, int *arr);
int is_prime(int num);
void transform(int **matrix, int *buf, int n, int m);

int main(void)
{
    int return_code = 0, buf[N][M], rows, columns, *matrix[N];
    transform(matrix, (int *)buf, N, M);
    printf("Input rows and columns: ");
    if (scanf("%d%d", &rows, &columns) != 2)
    {
        return_code = ERR_IO;
        printf("Invalid input!\n");
    }
    else if (rows <= 0 || rows > N || columns <= 0 || columns > M)
    {
        return_code = ERR_SIZE;
        printf("Matrix can't be lower than zero or bigger than ten!\n");
    }
    else if (input_matrix(matrix, rows, columns) == INP_ERR)
    {
        return_code = ERR_IO;
        printf("Invalid input!\n");
    }
    else
    {
        int primes[N * M];
        int primes_amount = fill_arr_with_primes(matrix, rows, columns, primes);
        if (primes_amount == 0)
        {
            return_code = ERR_NO_PRIMES;
            printf("No primes in matrix!\n");
        }
        else
        {
            reverse_array(primes, primes_amount);
            replace_primes(matrix, rows, columns, primes);
            printf("Resulting matrix:\n");
            print_matrix(matrix, rows, columns);
        }
    }

    return return_code;
}

void transform(int **matrix, int *buf, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        matrix[i] = buf + i * m;
    }
}

int fill_arr_with_primes(int **matrix, int rows, int cols, int *arr)
{
    int arr_size = 0, cur;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cur = matrix[i][j];
            if (is_prime(cur))
            {
                arr[arr_size++] = cur;
            }
        }
    }

    return arr_size;
}

void replace_primes(int **matrix, int rows, int cols, int *arr)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int cur = matrix[i][j];
            if (is_prime(cur))
            {
                matrix[i][j] = *(arr++);
            }
        }
    }
}

int is_prime(int num)
{
    int state = PRIME;
    if (num < 2)
    {
        state = NOT_PRIME;
    }
    else
    {
        for (int i = 2; (i <= num / 2) && (state == PRIME); i++)
        {
            if (num % i == 0)
            {
                state = NOT_PRIME;
            }
        }
    }

    return state;
}

void reverse_array(int *arr, int len)
{
    int temp;
    for (int i = 0; i < len / 2; i++)
    {
        temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }
}

int input_matrix(int **matrix, int rows, int cols)
{
    int return_code = OK;
    printf("Input matrix elements:\n");
    for (int i = 0; i < rows && return_code == OK; i++)
        for (int j = 0; j < cols && return_code == OK; j++)
            return_code = (scanf("%d", matrix[i] + j) == 1 ? OK : INP_ERR);
    return return_code;
}

void print_matrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        print_array(matrix[i], cols);
    }
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
