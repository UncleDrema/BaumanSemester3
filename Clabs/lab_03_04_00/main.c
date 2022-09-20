#include <stdio.h>
#define OK 0
#define INP_ERR -1
#define ERR_IO 1
#define ERR_SIZE 2
#define ERR_UNDEFINED 3
#define N 10
#define MINIMUM_FOUND 0
#define NOT_FOUND -1

int input_matrix(int **matrix, int rows, int cols);
int min_odd_number_under_main_diag(int **matrix, int size, int *min);
void transform(int **matrix, int *buf, int n, int m);

int main(void)
{
    int return_code = 0, buf[N][N], rows, columns, *matrix[N];
    transform(matrix, (int *)buf, N, N);
    printf("Input rows and columns: ");
    if (scanf("%d%d", &rows, &columns) != 2)
    {
        return_code = ERR_IO;
        printf("Invalid input!\n");
    }
    else if (rows <= 0 || rows > N || columns <= 0 || columns > N || (rows != columns))
    {
        return_code = ERR_SIZE;
        printf("Matrix should be squared and can't be lower than zero or bigger than ten!\n");
    }
    else if (rows == 1)
    {
        return_code = ERR_UNDEFINED;
        printf("No odd numbers under main diagonal!\n");
    }
    else if (input_matrix(matrix, rows, columns) == INP_ERR)
    {
        return_code = ERR_IO;
        printf("Invalid input!\n");
    }
    else
    {
        int result;
        if (min_odd_number_under_main_diag(matrix, rows, &result) == NOT_FOUND)
        {
            return_code = ERR_UNDEFINED;
            printf("No odd numbers under main diagonal!\n");
        }
        else
        {
            printf("Min odd number under main diag: %d\n", result);
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

int min_odd_number_under_main_diag(int **matrix, int size, int *min)
{
    int state = NOT_FOUND;
    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int cur = matrix[i][j];
            if (cur % 2 != 0 && (state == NOT_FOUND || cur < *min))
            {
                *min = cur;
                state = MINIMUM_FOUND;
            }
        }
    }

    return state;
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
