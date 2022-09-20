// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/10/22.
//
#include <stdio.h>
#include "err.h"
#include "film.h"
#include "err_io.h"
#include "utils.h"
#include <string.h>

#define MAX_FILMS 15

MAIN_ARGS(int argc, char *argv[])
{
    // Проверяем число аргументов
    if (argc < 3)
    {
        THROWN(NOT_ENOUGH_ARGS);
    }
    if (argc > 4)
    {
        THROWN(TOO_MUCH_ARGS);
    }

    char *file_name = argv[1];
    char *field_ame = argv[2];

    field_type_t field_type = CALL(err_get_field_type, field_ame);
    RETHROWN;

    int (*input_comparator)(film_t *, film_t *);

    switch (field_type)
    {
        case TITLE:
            input_comparator = compare_film_t_title;
            break;
        case NAME:
            input_comparator = compare_film_t_name;
            break;
        case YEAR:
            input_comparator = compare_film_t_year;
            break;
    }

    film_t films[MAX_FILMS];

    FILE *f = CALL(err_fopen, file_name, "r");
    RETHROWN;

    int len = CALL(err_read_film_t_arr_sorted, f, films, MAX_FILMS, input_comparator);
    RETHROWN;

    if (argc == 3)
    {
        print_film_t_arr(stdout, films, len);
    }
    else
    {
        char *query_string = argv[3];
        film_query_t query;
        int (*query_comparator)(film_t *, film_query_t *);

        switch (field_type)
        {
            case TITLE:
                strcpy(query.title, query_string);
                query_comparator = compare_film_query_title;
                break;
            case NAME:
                strcpy(query.name, query_string);
                query_comparator = compare_film_query_name;
                break;
            case YEAR:
                query.year = CALL(err_string_to_int, query_string);
                RETHROWN;
                query_comparator = compare_film_query_year;
                break;
        }

        film_t *found = CALL(err_find_film_binary, films, len, &query, query_comparator);
        CATCH_ONLY(NOT_FOUND,
            IGNORE;
            printf("Not found\n");
            return;
        )
        RETHROWN;

        print_film_t(stdout, found);
    }

    CALL(err_fclose, f);
    RETHROWN;
}