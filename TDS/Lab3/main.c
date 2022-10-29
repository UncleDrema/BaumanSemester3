//
// Created by archdrema on 10/28/22.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include "file.h"
#include "io.h"
#include "matrix.h"
#include "errors.h"

typedef enum
{
    EXIT,
    OUTPUT_CSR,
    OUTPUT_MATRIX,
    INPUT,
    ADD,
    ADD_PRINT
} MENU;

unsigned long long milliseconds_now(void);

err_t do_work(int argc, char **argv);

int main(int argc, char **argv)
{
    err_t rc = do_work(argc, argv);
    output_error(rc);
    return rc;
}

err_t do_work(int argc, char **argv)
{
    setbuf(stdout, NULL);
    int error_code = OK;
    if (argc != 3)
    {
        return ERROR_COMMAND_LINE;
    }
    char *filename1 = argv[1], *filename2 = argv[2];
    FILE *f1 = fopen(filename1, "r");
    if (!f1)
    {
        return ERROR_OPENING_FILE;
    }
    FILE *f2 = fopen(filename2, "r");
    if (!f2)
    {
        fclose(f1);
        return ERROR_OPENING_FILE;
    }

    int **matrix1, **matrix2;
    size_t n1, m1, nelems1, n2, m2, nelems2;
    error_code = matrix_create(f1, &matrix1, &n1, &m1, &nelems1, false);
    if (!error_code)
    {
        error_code = matrix_create(f2, &matrix2, &n2, &m2, &nelems2, false);
        if (!error_code)
        {
            sparse_matrix_t csr1, csr2;
            error_code = matrix_to_sparse(matrix1, n1, m1, nelems1, &csr1);
            if (!error_code)
            {
                error_code = matrix_to_sparse(matrix2, n2, m2, nelems2, &csr2);
                if (!error_code)
                {
                    bool run = true;
                    while (run && !error_code)
                    {
                        menu();
                        int command;
                        error_code = input_number(&command);
                        if (!error_code)
                        {
                            switch (command)
                            {
                                case EXIT:
                                {
                                    run = false;
                                    break;
                                }
                                case OUTPUT_CSR:
                                {
                                    puts("First:");
                                    sparse_output(stdout, &csr1);
                                    puts("\nSecond:");
                                    sparse_output(stdout, &csr2);
                                    break;
                                }
                                case OUTPUT_MATRIX:
                                {
                                    printf("First matrix: \n");
                                    matrix_output(stdout, matrix1, n1, m1);
                                    printf("\nSecond matrix: \n");
                                    matrix_output(stdout, matrix2, n2, m2);
                                    break;
                                }
                                case INPUT:
                                {
                                    error_code = matrix_create(stdin, &matrix1, &n1, &m1, &nelems1, true);
                                    if (!error_code)
                                    {
                                        error_code = matrix_create(stdin, &matrix2, &n2, &m2, &nelems2, true);
                                        if (!error_code)
                                        {
                                            error_code = matrix_to_sparse(matrix1, n1, m1, nelems1, &csr1);
                                            if (!error_code)
                                                error_code = matrix_to_sparse(matrix2, n2, m2, nelems2, &csr2);
                                        }
                                    }
                                    if (error_code)
                                    {
                                        n1 = 0; n2 = 0; m1 = 0; m2 = 0;
                                    }


                                    break;
                                }
                                case ADD:
                                {
                                    if (n1 == 0 || n2 == 0 || m1 == 0 || m2 == 0)
                                    {
                                        printf("Incorrect data");
                                    }
                                    else
                                    {
                                        sparse_matrix_t sum_result;
                                        unsigned long long beg, end, csr_time = 0, matrix_time = 0;
                                        bool printed = false;
                                        for (size_t i = 0; i < 1000 && !error_code; ++i)
                                        {
                                            error_code = sum_sparse_matrix_alloc(&csr1, &csr2, &sum_result);
                                            if (!error_code)
                                            {
                                                beg = milliseconds_now();
                                                sparse_matrix_sum(&csr1, &csr2, &sum_result);
                                                end = milliseconds_now();
                                                csr_time += end - beg;
                                            }
                                            if (!error_code)
                                            {
                                                if (!printed)
                                                {
                                                    //puts("Sparse form:");
                                                    //sparse_output(stdout, &sum_result);
                                                    printed = true;
                                                }
                                                free_sparse_matrix(&sum_result);
                                            }
                                        }
                                        if (!error_code)
                                        {
                                            size_t nr = n1, mr = m1;
                                            for (size_t i = 0; i < 1000 && !error_code; ++i)
                                            {
                                                int **result = matrix_alloc(nr, mr);
                                                if (!result)
                                                {
                                                    error_code = ERROR_MEMORY;
                                                }
                                                else
                                                {
                                                    beg = milliseconds_now();
                                                    error_code = matrix_sum(matrix1, matrix2, result, nr, mr);
                                                    if (!error_code)
                                                    {
                                                        end = milliseconds_now();
                                                        matrix_time += end - beg;
                                                        free(result);
                                                    }
                                                }
                                            }
                                        }
                                        if (!error_code)
                                        {
                                            size_t nr = n1, mr = m1;
                                            int **result = matrix_alloc(nr, mr);
                                            if (!result)
                                            {
                                                error_code = ERROR_MEMORY;
                                            }
                                            else
                                            {
                                                matrix_sum(matrix1, matrix2, result, nr, mr);
                                                //puts("Default form:");
                                                //matrix_output(stdout, result, nr, mr);
                                                free(result);
                                            }
                                            output_sum_result(csr_time, matrix_time, &sum_result);
                                        }
                                    }
                                    break;
                                }
                                case ADD_PRINT:
                                {
                                    if (n1 == 0 || n2 == 0 || m1 == 0 || m2 == 0)
                                    {
                                        printf("Incorrect data");
                                    }
                                    else
                                    {
                                        sparse_matrix_t sum_result;
                                        unsigned long long beg, end, csr_time = 0, matrix_time = 0;
                                        bool printed = false;
                                        for (size_t i = 0; i < 1 && !error_code; ++i)
                                        {
                                            error_code = sum_sparse_matrix_alloc(&csr1, &csr2, &sum_result);
                                            if (!error_code)
                                            {
                                                beg = milliseconds_now();
                                                sparse_matrix_sum(&csr1, &csr2, &sum_result);
                                                end = milliseconds_now();
                                                csr_time += end - beg;
                                            }
                                            if (!error_code)
                                            {
                                                if (!printed)
                                                {
                                                    puts("Sparse form:");
                                                    sparse_output(stdout, &sum_result);
                                                    printed = true;
                                                }
                                                free_sparse_matrix(&sum_result);
                                            }
                                        }
                                        if (!error_code)
                                        {
                                            size_t nr = n1, mr = m1;
                                            for (size_t i = 0; i < 1000 && !error_code; ++i)
                                            {
                                                int **result = matrix_alloc(nr, mr);
                                                if (!result)
                                                {
                                                    error_code = ERROR_MEMORY;
                                                }
                                                else
                                                {
                                                    beg = milliseconds_now();
                                                    error_code = matrix_sum(matrix1, matrix2, result, nr, mr);
                                                    if (!error_code)
                                                    {
                                                        end = milliseconds_now();
                                                        matrix_time += end - beg;
                                                        free(result);
                                                    }
                                                }
                                            }
                                        }
                                        if (!error_code)
                                        {
                                            size_t nr = n1, mr = m1;
                                            int **result = matrix_alloc(nr, mr);
                                            if (!result)
                                            {
                                                error_code = ERROR_MEMORY;
                                            }
                                            else
                                            {
                                                matrix_sum(matrix1, matrix2, result, nr, mr);
                                                puts("Default form:");
                                                matrix_output(stdout, result, nr, mr);
                                                free(result);
                                            }
                                        }
                                    }
                                    break;
                                }
                                default:
                                {
                                    error_code = ERROR_COMMAND;
                                    break;
                                }
                            }
                        }
                    }
                    free_sparse_matrix(&csr2);
                }
                free_sparse_matrix(&csr1);
            }
            free(matrix2);
        }
        free(matrix1);
    }

    return error_code;
}

unsigned long long milliseconds_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
        return (unsigned long long)-1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}
