#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "student.h"
#include "student_io.h"
#include "string_utils.h"

#define OK 0
#define ERR_ARGS 53
#define ERR_FIO 1
#define ERR_UNEXPECTED 2
#define ERR_EMPTY 3

#define UNSET 0
#define SET 1
#define SETTING_SRC 2
#define SETTING_DST 3
#define SETTING_SUBSTR 4

#define FLAG_COUNT 3
static char *flag_names[FLAG_COUNT] =
{
    "sb",
    "fb",
    "db"
};

typedef enum flags
{
    SORT,
    FPRINT,
    DELETE,
    NOT_A_FLAG
} flags;

#define EMPTY_ARGS {0, 0, 0, 0, NULL, NULL, NULL}

typedef struct arguments
{
    unsigned sort: 2;
    unsigned fprint: 3;
    unsigned delete: 2;
    unsigned errors: 1;
    char *file_src;
    char *file_dst;
    char *substr;
} arguments;

// Добавлено из-за проблем со стандартом С99+
int truncate(const char *, off_t);
flags parse_flag(const char *str);
void parse_args(arguments *args, int argc, char *argv[]);
int run(arguments *args);
#ifdef DEBUG
void print_args(arguments *args);
#endif
int run_sort(FILE *f);
int run_fprint(FILE *in, FILE *out, char *substr);
int run_delete(FILE *in, char *filename);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    arguments args = EMPTY_ARGS;
    parse_args(&args, argc, argv);

#ifdef DEBUG
    print_args(&args);
#endif

    return run(&args);
}

int run(arguments *args)
{
    int return_code = OK;

    if (args->errors)
        return_code = ERR_ARGS;
    else
    {
        FILE *f_src;
        if (args->fprint)
            f_src = fopen(args->file_src, "rb");
        else if (args->sort || args->delete)
            f_src = fopen(args->file_src, "rb+");
        else
            return_code = ERR_UNEXPECTED;

        if (!f_src)
            return_code = ERR_FIO;

        if (return_code == OK)
        {
            if (args->sort)
                return_code = run_sort(f_src);
            else if (args->delete)
                return_code = run_delete(f_src, args->file_src);
            else
            {
                FILE *f_dst = fopen(args->file_dst, "wb");
                if (!f_dst)
                    return_code = ERR_FIO;
                else
                    return_code = run_fprint(f_src, f_dst, args->substr);

                fclose(f_dst);
            }
            fclose(f_src);
        }
    }

    return return_code;
}

void parse_args(arguments *args, int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        char *cur_arg = argv[i];
        if (args->sort == SETTING_SRC)
        {
            args->file_src = cur_arg;
            args->sort = SET;
        }
        else if (args->delete == SETTING_SRC)
        {
            args->file_src = cur_arg;
            args->delete = SET;
        }
        else if (args->fprint == SETTING_SRC)
        {
            args->file_src = cur_arg;
            args->fprint = SETTING_DST;
        }
        else if (args->fprint == SETTING_DST)
        {
            args->file_dst = cur_arg;
            args->fprint = SETTING_SUBSTR;
        }
        else if (args->fprint == SETTING_SUBSTR)
        {
            args->substr = cur_arg;
            args->fprint = SET;
        }
        else
        {
            flags flag = parse_flag(cur_arg);
            switch (flag)
            {
                case SORT:
                    if (args->sort != UNSET)
                        args->errors = SET;
                    args->sort = SETTING_SRC;
                    break;
                case FPRINT:
                    if (args->fprint != UNSET)
                        args->errors = SET;
                    args->fprint = SETTING_SRC;
                    break;
                case DELETE:
                    if (args->delete != UNSET)
                        args->errors = SET;
                    args->delete = SETTING_SRC;
                    break;
                default:
                    args->errors = SET;
            }
        }
    }

    args->errors |= (args->sort + args->delete + args->fprint != 1);
}

int run_sort(FILE *f)
{
    int return_code = OK;
    int size = get_student_count(f);

    if (!size)
        return_code = ERR_EMPTY;
    else
    {
        rewind(f);
        int min_ind;
        student min_st, temp;
        for (int i = 0; i < size - 1; i++)
        {
            get_student_by_pos(f, i, &min_st);
            min_ind = i;
            for (int j = i + 1; j < size; j++)
            {
                get_student_by_pos(f, j, &temp);
                if (compare_students(&temp, &min_st) < 0)
                {
                    min_st = temp;
                    min_ind = j;
                }
            }

            if (i != min_ind)
            {
                get_student_by_pos(f, i, &temp);
                put_student_by_pos(f, i, &min_st);
                put_student_by_pos(f, min_ind, &temp);
            }
        }
    }

    return return_code;
}

int run_fprint(FILE *in, FILE *out, char *substr)
{
    int return_code = OK;
    if (strlen(substr) == 0)
        return_code = ERR_EMPTY;
    else
    {
        int count = 0, printed_count = 0;
        student st;
        fread(&st, sizeof(student), 1, in);
        while (!feof(in) && return_code == OK)
        {
            count++;
            int result = starts_with(st.surname, substr);
            if (result == ERR_PREFIX_TOO_BIG)
                return_code = ERR_EMPTY;
            else if (starts_with(st.surname, substr))
            {
                fwrite(&st, sizeof(student), 1, out);
                printed_count++;
            }
            fread(&st, sizeof(student), 1, in);
        }

        if (!count || !printed_count)
            return_code = ERR_EMPTY;
    }

    return return_code;
}

int run_delete(FILE *in, char *filename)
{
    int return_code = OK, count = 0;
    float average = 0;
    student st;
    fread(&st, sizeof(student), 1, in);
    while (!feof(in))
    {
        count++;
        average += av_mark(&st);
        fread(&st, sizeof(student), 1, in);
    }

    if (!count)
        return_code = ERR_EMPTY;
    else
    {
        average /= count;
        int j = 0;
        for (int i = 0; i < count; i++)
        {
            get_student_by_pos(in, i, &st);
            if (av_mark(&st) >= average)
                put_student_by_pos(in, j++, &st);
        }

        truncate(filename, sizeof(student) * j);
    }

    return return_code;
}

flags parse_flag(const char *str)
{
    flags flag = NOT_A_FLAG;
    for (int i = 0; i < FLAG_COUNT; i++)
        if (strcmp(str, flag_names[i]) == 0)
        {
            flag = i;
            break;
        }

    return flag;
}

#ifdef DEBUG
void print_args(arguments *args)
{
    printf("Errors: %d\n", args->errors);
    printf("Sort: %d\n", args->sort);
    printf("FPrint: %d\n", args->fprint);
    printf("Delete: %d\n", args->delete);
    printf("File_src: %s\n", args->file_src );
    printf("File_dst: %s\n", args->file_dst);
    printf("Substr: %s\n", args->substr);
}
#endif
