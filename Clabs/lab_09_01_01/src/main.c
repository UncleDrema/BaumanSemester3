// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 10/28/22.
// Основная программа

#include <stdio.h>
#include <err.h>
#include <film.h>
#include <utils.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    err_t rc;
    // Проверяем число аргументов
    if (argc < 3)
    {
        return NOT_ENOUGH_ARGS;
    }
    if (argc > 4)
    {
        return TOO_MUCH_ARGS;
    }

    char *file_name = argv[1];
    char *field_name = argv[2];

    field_type_t field_type;
    rc = get_field_type(field_name, &field_type);
    if (rc != OK)
    {
        return rc;
    }

    int (*input_comparator)(const film_t *, const film_t *);

    switch (field_type)
    {
        case TITLE:
            input_comparator = compare_film_title;
            break;
        case NAME:
            input_comparator = compare_film_name;
            break;
        case YEAR:
            input_comparator = compare_film_year;
            break;
    }

    film_t *films;

    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        return OPEN_ERR;
    }

    size_t len;
    rc = read_film_arr_sorted(f, &films, input_comparator, &len);
    fclose(f);
    if (rc != OK)
    {
        if (rc != ALLOC_ERR)
        {
            free_film_arr(films, len);
        }
        return rc;
    }

    if (argc == 3)
    {
        print_film_arr(stdout, films, len);
    }
    else
    {
        char *query_string = argv[3];
        film_query_t query;
        int (*query_comparator)(const film_t *, const film_query_t *);

        switch (field_type)
        {
            case TITLE:
                query.title = query_string;
                query_comparator = compare_film_query_title;
                break;
            case NAME:
                query.name = query_string;
                query_comparator = compare_film_query_name;
                break;
            case YEAR:
                rc = string_to_int(query_string, &query.year);
                if (rc != OK)
                {
                    free_film_arr(films, len);
                    return rc;
                }
                query_comparator = compare_film_query_year;
                break;
        }

        film_t *found;
        rc = find_film_binary(films, len, &query, query_comparator, &found);
        if (rc == NOT_FOUND)
        {
            puts("Not found");
            rc = OK;
        }
        else
        {
            print_film(stdout, found);
        }
    }
    free_film_arr(films, len);

    return rc;
}