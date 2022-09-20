#include <stdio.h>
#define OK 0
#define INP_ERR -1
#define ERR_IO 1
#define ERR_SIZE 2
#define N 10
#define M 10

void fill_matrix_bull(int **matrix, int rows, int cols);
void print_matrix(int **matrix, int rows, int cols);
void print_array(int *arr, int len);
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
    else
    {
        fill_matrix_bull(matrix, rows, columns);
        print_matrix(matrix, rows, columns);
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

void fill_matrix_bull(int **matrix, int rows, int cols)
{
    int num = 1;

    for (int j = 0; j < cols; j++)
    {
        if (j % 2 == 0)
        {
            for (int i = 0; i < rows; i++)
            {
                matrix[i][j] = num++;
            }
        }
        else
        {
            for (int i = rows - 1; i >= 0; i--)
            {
                matrix[i][j] = num++;
            }
        }
    }
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
