// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/12/22.
//
// Вариант 15, формат: 21
#include <stdio.h>
#include <string.h>
#include <err.h>
#include <matrix.h>
#include <matrix_io.h>

#define SAFE_CLOSE(f) if (f != NULL) fclose(f)

/// Типы операций
typedef enum
{
    /// Сложение
    ADD,
    /// Умножение
    MULTIPLY,
    /// Поиск обратной матрицы
    REVERSE,
    /// Некорректная операция
    NOT_AN_OPERATION
} action_t;

/// Получить тип действия из строки
action_t get_action_type(char *argument);

int main(int argc, char *argv[])
{
    err_t rc = OK;
    if (argc < 4 || argc > 5)
    {
        rc = ARGS_ERR;
    }
    else
    {
        action_t action = get_action_type(argv[1]);

        if (action == NOT_AN_OPERATION || (action == REVERSE && argc == 5))
        {
            rc = ARGS_ERR;
        }
        else
        {
            FILE *mat1, *res;
            matrix_t m1, m_res;
            if (action == REVERSE)
            {
                mat1 = fopen(argv[2], "r");
                res = fopen(argv[3], "w");

                if (mat1 == NULL || res == NULL)
                {
                    rc = IO_ERR;
                }

                if (rc == OK)
                {
                    matrix_t m1, m_res;

                    rc = input_coordinate_form(mat1, &m1);

                    if (rc != MEMORY_ERR)
                    {
                        if (rc == OK)
                        {
                            rc = matrix_rev(&m1, &m_res);

                            if (rc != MEMORY_ERR)
                            {
                                if (rc == OK)
                                {
                                    rc = print_simple_format(res, &m_res);
                                }
                                free_matrix(&m_res);
                            }
                            free_matrix(&m1);
                        }
                    }
                }

                SAFE_CLOSE(mat1);
                SAFE_CLOSE(res);
            }
            else
            {
                FILE *mat2;

                mat1 = fopen(argv[2], "r");
                mat2 = fopen(argv[3], "r");
                res = fopen(argv[4], "w");

                if (mat1 == NULL || mat2 == NULL || res == NULL)
                {
                    rc = IO_ERR;
                }

                if (rc == OK)
                {
                    matrix_t m2;

                    rc = input_coordinate_form(mat1, &m1);

                    if (rc != MEMORY_ERR)
                    {
                        if (rc == OK)
                        {
                            rc = input_coordinate_form(mat2, &m2);

                            if (rc != MEMORY_ERR)
                            {
                                if (rc == OK)
                                {
                                    if (action == ADD)
                                    {
                                        rc = matrix_add(&m1, &m2, &m_res);
                                    }
                                    else
                                    {
                                        rc = matrix_mul(&m1, &m2, &m_res);
                                    }

                                    if (rc != MEMORY_ERR)
                                    {
                                        if (rc == OK)
                                        {
                                            rc = print_simple_format(res, &m_res);
                                            free_matrix(&m_res);
                                        }
                                    }
                                    free_matrix(&m2);
                                }
                            }
                        }

                        free_matrix(&m1);
                    }
                }

                SAFE_CLOSE(mat1);
                SAFE_CLOSE(mat2);
                SAFE_CLOSE(res);
            }
        }
    }
    return rc;
}

action_t get_action_type(char *argument)
{
    if (strcmp(argument, "a") == 0)
    {
        return ADD;
    }
    else if (strcmp(argument, "m") == 0)
    {
        return MULTIPLY;
    }
    else if (strcmp(argument, "o") == 0)
    {
        return REVERSE;
    }
    else
    {
        return NOT_AN_OPERATION;
    }
}
