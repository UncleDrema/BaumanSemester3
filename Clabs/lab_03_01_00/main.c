#include <stdio.h>
#define OK 0
#define INP_ERR -1
#define ERR_IO 1
#define ERR_SIZE 2
#define ORDERED 0
#define NOT_ORDERED 1
#define N 10
#define M 10

int input_matrix(int **matrix, int rows, int cols);
void print_array(int *arr, int len);
void process_matrix(int **matrix, int *result, int rows, int cols);
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
        int arr[M];
        process_matrix(matrix, arr, rows, columns);
        print_array(arr, columns);
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

void process_matrix(int **matrix, int *result, int rows, int cols)
{
    int state, prev, cur;
    for (int j = 0; j < cols; j++)
    {
        state = ORDERED;
        prev = matrix[0][j];
        for (int i = 1; i < rows && (state == ORDERED); i++)
        {
            cur = matrix[i][j];
            if (cur >= prev)
                state = NOT_ORDERED;
            prev = cur;
        }
        result[j] = (state == ORDERED) && (rows > 1) ? 1 : 0;
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
