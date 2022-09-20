#include <stdio.h>
#define OK 0
#define INP_ERR -1
#define ERR_IO 1
#define ERR_SIZE 2
#define ERR_NOT_DIGIT 3
#define N 10
#define M 10
#define VALID 1
#define NOT_VALID 0
#define FILLER 100

int input_matrix(int **matrix, int rows, int cols);
void print_matrix(int **matrix, int rows, int cols);
void print_array(int *arr, int len);
int is_valid_row(int *row, int len, int digit);
int process_matrix(int **matrix, int rows, int cols, int **new_matrix, int digit);
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
        int digit;
        printf("Input your digit: ");
        if (scanf("%d", &digit) != 1)
        {
            return_code = ERR_IO;
            printf("Invalid input!\n");
        }
        else if (digit < 0 || digit > 9)
        {
            return_code = ERR_NOT_DIGIT;
            printf("Digit must be from zero to nine!\n");
        }
        else
        {
            int new_buf[2 * N][M], *new_matrix[2 * N];
            transform(new_matrix, (int *)new_buf, N, M);
            int new_rows = process_matrix(matrix, rows, columns, new_matrix, digit);
            print_matrix(new_matrix, new_rows, columns);
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

int process_matrix(int **matrix, int rows, int cols, int **new_matrix, int digit)
{
    int new_rows = 0;
    for (int i = 0; i < rows; i++, new_rows++)
    {
        for (int j = 0; j < cols; j++)
        {
            new_matrix[new_rows][j] = matrix[i][j];
        }

        if (is_valid_row(matrix[i], cols, digit))
        {
            new_rows++;
            for (int j = 0; j < cols; j++)
            {
                new_matrix[new_rows][j] = FILLER;
            }
        }
    }

    return new_rows;
}

int is_valid_row(int *row, int len, int digit)
{
    int first_digit = 0, last_digit = 0, el;
    for (int i = 0; i < len; i++)
    {
        el = row[i] >= 0 ? row[i] : -row[i];
        if (el % 10 == digit)
        {
            last_digit++;
        }

        while (el >= 10)
            el /= 10;
        if (el == digit)
        {
            first_digit++;
        }
    }

    return ((first_digit == last_digit) && (first_digit > 0)) ? VALID : NOT_VALID;
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
