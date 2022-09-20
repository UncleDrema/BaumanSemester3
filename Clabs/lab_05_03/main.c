/*
 * Для реализации данной задачи в качестве используемого целочисленного типа данных был выбран int
 * Для функции сортировки выбран простой алгоритм сотировки выбором,
 * Сортировка происходит в направлении от меньшего к большему
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "num_utils.h"
#include "binary_io.h"
#include "standart_converts.h"

#define OK 0
#define ERR_WRONG_FLAGS 1
#define ERR_ACTION 2
#define ERR_FIO 3

#define UNSET 0
#define SET 1
#define SETTING_NUMBER 2

typedef enum Errors {
    NO_ERR = 0,
    ERR_FLAGS = 1,
    ERR_NO_FILE = 2,
    ERR_NO_NUMBER = 4,
    ERR_INVALID_NUMBER = 8
} Errors;

#define FLAG_COUNT 3
static char *FlagNames[FLAG_COUNT] = {
    "c",
    "p",
    "s"
};

typedef enum Flags {
    CREATE,
    PRINT,
    SORT,
    NOT_A_FLAG
} Flags;

#define EMPTY_ARGS {0, 0, 0, 0, 0, NULL}

typedef struct arguments {
    unsigned create: 2;
    unsigned print: 1;
    unsigned sort: 1;
    Errors errors: 4;
    int number;
    const char *file;
} Arguments;

Flags parse_flag(const char *str);
void parse_args(Arguments *args, int argc, char *argv[]);
int run(Arguments *args);
void print_err_msg(Errors err);
void run_create(FILE *file, int size);
int run_print(FILE *file);
int run_sort(FILE *file);
#ifdef DEBUG
void print_args(Arguments *args);
#endif

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Arguments args = EMPTY_ARGS;
    parse_args(&args, argc, argv);

#ifdef DEBUG
    print_args(&args);
#endif

    return run(&args);
}

int run(Arguments *args)
{
    int return_code = OK;
    if (args->errors != NO_ERR)
    {
        print_err_msg(args->errors);
        return_code = ERR_WRONG_FLAGS;
    }
    else
    {
        FILE *f;
        if (args->create)
        {
            f = fopen(args->file, "wb");
        }
        else if (args->print)
        {
            f = fopen(args->file, "rb");
        }
        else if (args->sort)
        {
            f = fopen(args->file, "rb+");
        }

        if (f == NULL)
        {
            puts("Error on file open!");
            return_code = ERR_FIO;
        }
        else
        {
            if (args->create)
            {
                run_create(f, args->number);
            }
            else if (args->print)
            {
                return_code = run_print(f);
            }
            else if (args->sort)
            {
                return_code = run_sort(f);
            }

            fclose(f);
        }
    }

    return return_code;
}

void print_err_msg(Errors err)
{
    if (err & ERR_FLAGS)
        puts("Wrong flags!");
    if (err & ERR_NO_FILE)
        puts("No target file specified!");
    if (err & ERR_NO_NUMBER)
        puts("No file size to generate specified!");
    if (err & ERR_INVALID_NUMBER)
        puts("Invalid number inputed! Number must be positive!");
}

void run_create(FILE *file, int size)
{
    int num;
    for (int i = 0; i < size; i++)
    {
        num = rand_range(-50, 50);
        fwrite(&num, sizeof(int), 1, file);
    }
}

int run_print(FILE *file)
{
    int return_code = OK;
    if (get_number_count(file) < 1)
        return_code = ERR_ACTION;
    rewind(file);
    CONVERT_B2T(int, file, stdout, " ", "\n");
    return return_code;
}

int run_sort(FILE *file)
{
    int n = get_number_count(file), min_el, min_ind, temp, return_code = OK;
    rewind(file);
    for (int i = 0; i < n - 1; i++)
    {
        min_el = get_number_by_pos(file, i);
        min_ind = i;
        for (int j = i + 1; j < n; j++)
        {
            temp = get_number_by_pos(file, j);
            if (temp < min_el)
            {
                min_el = temp;
                min_ind = j;
            }
        }
        temp = get_number_by_pos(file, i);
        put_number_by_pos(file, i, min_el);
        put_number_by_pos(file, min_ind, temp);
    }
    if (n < 1)
        return_code = ERR_ACTION;
    return return_code;
}

void parse_args(Arguments *args, int argc, char *argv[])
{
    for (int i = 1; i < argc - 1; i++)
    {
        char *cur_arg = argv[i];
        if (args->create == SETTING_NUMBER)
        {
            if (to_number_safe(cur_arg, &args->number))
            {
                args->create = SET;
            }
            else
            {
                args->errors |= ERR_INVALID_NUMBER;
            }
        }
        else
        {
            Flags flag = parse_flag(cur_arg);
            switch (flag)
            {
                case CREATE:
                    if (args->create != UNSET)
                        args->errors |= ERR_FLAGS;
                    args->create = SETTING_NUMBER;
                    break;
                case PRINT:
                    if (args->print & SET)
                        args->errors |= ERR_FLAGS;
                    args->print = SET;
                    break;
                case SORT:
                    if (args->sort & SET)
                        args->errors |= ERR_FLAGS;
                    args->sort = SET;
                    break;
                default:
                    args->errors |= ERR_FLAGS;
            }
        }
    }

    args->file = argv[argc - 1];

    if (args->create + args->print + args->sort != 1)
        args->errors |= ERR_FLAGS;
    if (args->file == NULL)
            args->errors |= ERR_NO_FILE;
    if (args->create != UNSET)
    {
        if (args->create == SETTING_NUMBER)
            args->errors |= ERR_NO_NUMBER;
        else if (args->number <= 0)
            args->errors |= ERR_INVALID_NUMBER;

    }
}

Flags parse_flag(const char *str)
{
    Flags flag = NOT_A_FLAG;
    for (int i = 0; i < FLAG_COUNT; i++)
        if (strcmp(str, FlagNames[i]) == 0)
        {
            flag = i;
            break;
        }

    return flag;
}

#ifdef DEBUG
void print_args(Arguments *args)
{
    printf("Create: %d\n", args->create);
    printf("Print: %d\n", args->print);
    printf("Sort: %d\n", args->sort);
    printf("Errors: %d\n", args->errors);
    printf("Number: %d\n", args->number);
    printf("File: %s\n", args->file);
}
#endif
