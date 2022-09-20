// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/10/22.
//

#include "film.h"
#include <string.h>
#include "utils.h"

FUNC(field_type_t, err_get_field_type, char *str)
{
    field_type_t res;
    if (strcmp(str, "title") == 0)
    {
        res = TITLE;
    }
    else if (strcmp(str, "name") == 0)
    {
        res = NAME;
    }
    else if (strcmp(str, "year") == 0)
    {
        res = YEAR;
    }
    else
    {
        THROW(WRONG_FIELD, -1);
    }

    return res;
}

void print_film_t(FILE *f, film_t *film)
{
    fprintf(f, "%s\n", film->title);
    fprintf(f, "%s\n", film->name);
    fprintf(f, "%d\n", film->year);
}

FUNC(void, err_read_film_t, FILE *f, film_t *film)
{
    if (fgets(film->title, FILM_TITLE_LEN, f) == NULL)
    {
        if (feof(f))
        {
            THROWN(INPUT_END);
        }
        else
        {
            THROWN(FILM_WRONG_FORMAT);
        }
    }

    char *new_line;

    new_line = strchr(film->title, '\n');
    if (new_line != NULL)
    {
        *new_line = '\0';
    }
    else
    {
        if (skip_to_nl(f) != 1)
        {
            THROWN(FILM_WRONG_FORMAT);
        }
    }

    if (strlen(film->title) == 0)
    {
        THROWN(FILM_WRONG_FORMAT);
    }

    if (fgets(film->name, FILM_NAME_LEN, f) == NULL)
    {
        THROWN(FILM_WRONG_FORMAT);
    }

    new_line = strchr(film->name, '\n');
    if (new_line != NULL)
    {
        *new_line = '\0';
    }
    else
    {
        if (skip_to_nl(f) != 1)
        {
            THROWN(FILM_WRONG_FORMAT);
        }
    }

    if (strlen(film->name) == 0)
    {
        THROWN(FILM_WRONG_FORMAT);
    }

    if (fscanf(f, "%d", &film->year) != 1 || film->year <= 0)
    {
        THROWN(FILM_WRONG_FORMAT);
    }

    skip_to_nl(f);
}

void print_film_t_arr(FILE *f, film_t *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        print_film_t(f, arr + i);
    }
}

static int find_insert_position(film_t *film, film_t *arr, int len, int (*comparator)(film_t *, film_t *))
{
    if (len == 0)
    {
        return 0;
    }

    int i;

    for (i = 0; i < len && comparator(film, arr + i) >= 0; i++);

    return i;
}

FUNC(int, err_read_film_t_arr_sorted, FILE *f, film_t *arr, int max_len, int (*comparator)(film_t *, film_t *))
{
    int len;
    film_t temp;

    for (len = 0; len <= max_len; len++)
    {
        CALL(err_read_film_t, f, &temp);
        RETHROW_ONLY(FILM_WRONG_FORMAT, 0);
        CATCH_ONLY(INPUT_END,
            IGNORE;
            break;
        )

        if (len == max_len)
        {
            THROW(TOO_MUCH_ENTRIES, 0);
        }

        int insert_pos = find_insert_position(&temp, arr, len, comparator);
        for (int i = len; i > insert_pos; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[insert_pos] = temp;
    }

    if (len == 0)
    {
        THROW(INPUT_END, 0);
    }

    return len;
}

int compare_film_t_title(film_t *a, film_t *b)
{
    return strcmp(a->title, b->title);
}

int compare_film_t_name(film_t *a, film_t *b)
{
    return strcmp(a->name, b->name);
}

int compare_film_t_year(film_t *a, film_t *b)
{
    return a->year - b->year;
}

int compare_film_query_title(film_t *a, film_query_t *b)
{
    return strcmp(a->title, b->title);
}

int compare_film_query_name(film_t *a, film_query_t *b)
{
    return strcmp(a->name, b->name);
}

int compare_film_query_year(film_t *a, film_query_t *b)
{
    return a->year - b->year;
}

FUNC(film_t*, err_find_film_binary, film_t *arr, int len, film_query_t *query, int (*comparator)(film_t *, film_query_t*))
{
    int l = 0;
    int r = len - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        film_t *mid_val = arr + mid;
        int cmp = comparator(mid_val, query);
        if (cmp < 0)
        {
            l = mid + 1;
        }
        else if (cmp > 0)
        {
            r = mid - 1;
        }
        else
        {
            return mid_val;
        }
    }

    THROW(NOT_FOUND, NULL);
}