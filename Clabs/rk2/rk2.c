#include <stdio.h>
#include <string.h>

#define N 5
#define WORD_SIZE 5
#define INVALID_LEN -1

typedef struct sqMatrix
{
    int size;
    char *matrix[N][N];
    char buf[N][N][WORD_SIZE];
} SquareMatrix;

void init_matrix(SquareMatrix *matrix);

void input_word_matrix(SquareMatrix *matrix);

int count_eq_len_columns(SquareMatrix *matrix);

int main(void)
{
    SquareMatrix matr;
    SquareMatrix *p_matr = &matr;
    init_matrix(p_matr);
    input_word_matrix(p_matr);

    printf("%d\n", count_eq_len_columns(p_matr));
    return 0;
}

int count_eq_len_columns(SquareMatrix *matrix)
{
    int size = matrix->size;
    int count = 0;
    for (int col = 0; col < size; col++)
    {
        int len = strlen(matrix->matrix[0][col]);
        count++;
        for (int row = 1; row < size; row++)
        {
            if (strlen(matrix->matrix[row][col]) != len)
            {
                count--;
                break;
            }
        }
    }

    return count;
}

void init_matrix(SquareMatrix *matrix)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            char *word = matrix->buf[i][j];
            matrix->matrix[i][j] = word;
        }
}

void input_word_matrix(SquareMatrix *matrix)
{
    int size;
    scanf("%d", &size);
    matrix->size = size;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            scanf("%s", matrix->matrix[i][j]);
        }
}
