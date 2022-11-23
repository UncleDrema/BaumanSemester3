// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 10/28/22.
// Реализация функций обработки информации о фильмах

#include <film.h>
#include <string.h>
#include <utils.h>
#include <stdlib.h>

err_t get_field_type(char *str, field_type_t *out)
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
        return WRONG_FIELD;
    }

    *out = res;
    return OK;
}

void print_film(FILE *f, const film_t *film)
{
    fprintf(f, "%s\n", film->title);
    fprintf(f, "%s\n", film->name);
    fprintf(f, "%d\n", film->year);
}

err_t read_film(FILE *f, film_t *film)
{
    film->title = NULL;
    film->name = NULL;

    size_t len;
    if (getline(&film->title, &len, f) <= 0)
    {
        if (feof(f))
        {
            return INPUT_END;
        }
        else
        {
            return FILM_WRONG_FORMAT;
        }
    }

    char *new_line;

    if (film->title != NULL)
    {
        new_line = strchr(film->title, '\n');
        if (new_line != NULL)
        {
            *new_line = '\0';
        }

        if (*film->title == '\0')
        {
            return FILM_WRONG_FORMAT;
        }
    }

    if (getline(&film->name, &len, f) <= 0)
    {
        return FILM_WRONG_FORMAT;
    }

    if (film->name != NULL)
    {
        new_line = strchr(film->name, '\n');
        if (new_line != NULL)
        {
            *new_line = '\0';
        }

        if (*film->name == '\0')
        {
            return FILM_WRONG_FORMAT;
        }
    }

    if (fscanf(f, "%d", &film->year) != 1 || film->year <= 0)
    {
        return FILM_WRONG_FORMAT;
    }

    skip_to_nl(f);

    if (film->title == NULL || film->name == NULL)
    {
        return ALLOC_ERR;
    }
    return OK;
}

void print_film_arr(FILE *f, const film_t *arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        print_film(f, arr + i);
    }
}

static size_t find_insert_position(film_t *film, film_t *arr, size_t len, int (*comparator)(const film_t *, const film_t *))
{
    size_t i;

    for (i = 0; i < len && comparator(film, arr + i) >= 0; i++);

    return i;
}

static void insert_at_position(const film_t *film, film_t *arr, size_t insert_pos, size_t len)
{
    for (size_t i = len; i > insert_pos; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[insert_pos] = *film;
}

static err_t count_film_entries(FILE *f, size_t *count)
{
    film_t temp;

    for (*count = 0; ; (*count)++)
    {
        err_t rc = read_film(f, &temp);
        free_film(&temp);

        if (rc == INPUT_END)
        {
            break;
        }

        if (rc != OK)
        {
            return ALLOC_ERR;
        }
    }

    return OK;
}

err_t read_film_arr_sorted(FILE *f, film_t **arr, int (*comparator)(const film_t *, const film_t *), size_t *len)
{
    film_t temp;

    err_t rc = count_film_entries(f, len);
    if (rc != OK)
    {
        return rc;
    }

    rewind(f);

    if (*len == 0)
    {
        return ALLOC_ERR;
    }

    *arr = malloc(*len * sizeof(film_t));
    if (*arr == NULL)
    {
        return ALLOC_ERR;
    }

    for (size_t i = 0; i < *len; i++)
    {
        rc = read_film(f, &temp);
        if (rc != OK)
        {
            free_film_arr(*arr, i);
            if (rc == INPUT_END)
            {
                rc = FILM_WRONG_FORMAT;
            }
            return rc;
        }

        size_t insert_pos = find_insert_position(&temp, *arr, i, comparator);
        insert_at_position(&temp, *arr, insert_pos, i);
    }

    return OK;
}

int compare_film_title(const film_t *a, const film_t *b)
{
    return strcmp(a->title, b->title);
}

int compare_film_name(const film_t *a, const film_t *b)
{
    return strcmp(a->name, b->name);
}

int compare_film_year(const film_t *a, const film_t *b)
{
    return a->year - b->year;
}

int compare_film_query_title(const film_t *a, const film_query_t *b)
{
    return strcmp(a->title, b->title);
}

int compare_film_query_name(const film_t *a, const film_query_t *b)
{
    return strcmp(a->name, b->name);
}

int compare_film_query_year(const film_t *a, const film_query_t *b)
{
    return a->year - b->year;
}

err_t find_film_binary(film_t *arr, size_t len, film_query_t *query, int (*comparator)(const film_t *, const film_query_t*), film_t **res_film)
{
    if (arr == NULL || query == NULL || comparator == NULL || res_film == NULL || len == 0)
    {
        return WRONG_DATA;
    }

    size_t l = 0;
    size_t r = len - 1;
    while (l <= r && r < len)
    {
        size_t mid = (l + r) / 2;
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
            *res_film = mid_val;
            return OK;
        }
    }

    *res_film = NULL;
    return NOT_FOUND;
}

void free_film(film_t *film)
{
    if (film != NULL)
    {
        if (film->title)
        {
            free(film->title);
        }
        if (film->name)
        {
            free(film->name);
        }
    }
}

void free_film_arr(film_t *arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        free_film(arr + i);
    }

    free(arr);
}