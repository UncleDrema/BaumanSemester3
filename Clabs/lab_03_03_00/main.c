#include <stdio.h>
#define OK 0
#define INP_ERR -1
#define ERR_IO 1
#define ERR_SIZE 2
#define N 10
#define M 10

int input_matrix(int **matrix, int rows, int cols);
void print_matrix(int **matrix, int rows, int cols);
void print_array(int *arr, int len);
int array_sum(int *row, int len);
void sort_matrix_by_rows(int **matrix, int rows, int cols);
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
        sort_matrix_by_rows(matrix, rows, columns);
        printf("Sorted matrix: \n");
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

int array_sum(int *row, int len)
{
    int s = 0;
    for (int i = 0; i < len; i++)
        s += row[i];

    return s;
}

void sort_matrix_by_rows(int **matrix, int rows, int cols)
{
    int *temp;
    for (int i = 0; i < rows - 1; i++)
    {
        int min_row_ind = i;
        int min_row_sum = array_sum(matrix[min_row_ind], cols);
        for (int j = i; j < rows; j++)
        {
            int cur_sum = array_sum(matrix[j], cols);
            if (cur_sum < min_row_sum)
            {
                min_row_sum = cur_sum;
                min_row_ind = j;
            }
        }

        temp = matrix[i];
        matrix[i] = matrix[min_row_ind];
        matrix[min_row_ind] = temp;
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
