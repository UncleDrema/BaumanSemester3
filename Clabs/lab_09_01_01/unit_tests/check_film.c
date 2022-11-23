// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 10/28/22.
// Юнит тесты film.h

#include <check_film.h>
#include <film.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/// Проверяем получение типа поля заголовок из строки "title"
START_TEST(get_field_title)
{
    field_type_t field_type;
    err_t rc = get_field_type("title", &field_type);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(field_type, TITLE);
}
END_TEST

/// Проверяем получение типа поля имя автора из строки "name"
START_TEST(get_field_name)
{
    field_type_t field_type;
    err_t rc = get_field_type("name", &field_type);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(field_type, NAME);
}
END_TEST

/// Проверяем получение типа поля год выхода из строки "year"
START_TEST(get_field_year)
{
    field_type_t field_type;
    err_t rc = get_field_type("year", &field_type);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(field_type, YEAR);
}
END_TEST

/// Проверяем получение ошибки из некорректной строки типа поля
START_TEST(get_field_wrong)
{
    field_type_t field_type;
    err_t rc = get_field_type("alalakek", &field_type);

    ck_assert_int_eq(rc, WRONG_FIELD);
}
END_TEST

/// Проверяем получение ошибки при получении типа поля из пустой строки
START_TEST(get_field_empty)
{
    field_type_t field_type;
    err_t rc = get_field_type("", &field_type);

    ck_assert_int_eq(rc, WRONG_FIELD);
}
END_TEST

/// Проверка корректного поиска фильма по названию
START_TEST(find_film_by_title)
{
    film_t films[] =
    {
            { "A", "SomeA", 1990 },
            { "B", "SomeB", 1991 },
            { "C", "SomeC", 1992 },
            { "D", "SomeD", 1993 }
    };

    film_query_t q = {.title = "C"};
    film_t *res = NULL;

    err_t rc = find_film_binary(films, 4, &q, compare_film_query_title, &res);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_eq(res, films + 2);
}
END_TEST

/// Проверка корректного поиска фильма по названию (фильм отсутствует)
START_TEST(find_film_by_title_nf)
{
    film_t films[] =
            {
                    { "A", "SomeA", 1990 },
                    { "B", "SomeB", 1991 },
                    { "C", "SomeC", 1992 },
                    { "D", "SomeD", 1993 }
            };

    film_query_t q = { .title = "E" };
    film_t *res = NULL;

    err_t rc = find_film_binary(films, 4, &q, compare_film_query_title, &res);

    ck_assert_int_eq(rc, NOT_FOUND);
    ck_assert_ptr_eq(res, NULL);
}
END_TEST

/// Проверка корректного поиска фильма по имени автора
START_TEST(find_film_by_name)
{
    film_t films[] =
            {
                    { "A", "SomeA", 1990 },
                    { "B", "SomeB", 1991 },
                    { "C", "SomeC", 1992 },
                    { "D", "SomeD", 1993 }
            };

    film_query_t q = { .name = "SomeB" };
    film_t *res = NULL;

    err_t rc = find_film_binary(films, 4, &q, compare_film_query_name, &res);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_eq(res, films + 1);
}
END_TEST

/// Проверка корректного поиска фильма по имени автора (не найдено)
START_TEST(find_film_by_name_nf)
{
    film_t films[] =
            {
                    {"A", "SomeA", 1990},
                    {"B", "SomeB", 1991},
                    {"C", "SomeC", 1992},
                    {"D", "SomeD", 1993}
            };

    film_query_t q = {.name = "SomeE"};
    film_t *res = NULL;

    err_t rc = find_film_binary(films, 4, &q, compare_film_query_name, &res);

    ck_assert_int_eq(rc, NOT_FOUND);
    ck_assert_ptr_eq(res, NULL);
}
END_TEST

/// Проверка корректного поиска фильма по году выхода
START_TEST(find_film_by_year)
{
    film_t films[] =
            {
                    { "A", "SomeA", 1990 },
                    { "B", "SomeB", 1991 },
                    { "C", "SomeC", 1992 },
                    { "D", "SomeD", 1993 }
            };

    film_query_t q = { .year = 1990 };
    film_t *res = NULL;

    err_t rc = find_film_binary(films, 4, &q, compare_film_query_year, &res);

    ck_assert_int_eq(rc, OK);
    ck_assert_ptr_eq(res, films);
}
END_TEST

/// Проверка корректного поиска фильма по году выхода (не найдено)
START_TEST(find_film_by_year_nf)
{
    film_t films[] =
            {
                    { "A", "SomeA", 1990 },
                    { "B", "SomeB", 1991 },
                    { "C", "SomeC", 1992 },
                    { "D", "SomeD", 1993 }
            };

    film_query_t q = { .year = 1994 };
    film_t *res = NULL;

    err_t rc = find_film_binary(films, 4, &q, compare_film_query_year, &res);

    ck_assert_int_eq(rc, NOT_FOUND);
    ck_assert_ptr_eq(res, NULL);
}
END_TEST

/// Проверка обработки поиска по null массиву
START_TEST(find_film_arr_null)
{
    film_query_t q = { .year = 1990 };
    film_t *res = NULL;

    err_t rc = find_film_binary(NULL, 4, &q, compare_film_query_year, &res);

    ck_assert_int_eq(rc, WRONG_DATA);
}
END_TEST

/// Проверка обработки поиска по null запросу
START_TEST(find_film_query_null)
{
    film_t films[] =
            {
                    { "A", "SomeA", 1990 },
                    { "B", "SomeB", 1991 },
                    { "C", "SomeC", 1992 },
                    { "D", "SomeD", 1993 }
            };

    film_t *res = NULL;

    err_t rc = find_film_binary(films, 4, NULL, compare_film_query_year, &res);

    ck_assert_int_eq(rc, WRONG_DATA);
}
END_TEST

/// Проверка поиска фильма с null компаратором
START_TEST(find_film_cmp_null)
{
    film_t films[] =
            {
                    { "A", "SomeA", 1990 },
                    { "B", "SomeB", 1991 },
                    { "C", "SomeC", 1992 },
                    { "D", "SomeD", 1993 }
            };

    film_query_t q = { .year = 1990 };
    film_t *res = NULL;

    err_t rc = find_film_binary(films, 4, &q, NULL, &res);

    ck_assert_int_eq(rc, WRONG_DATA);
}
END_TEST

/// Проверка обработки поиска фильма с null переменной для записи результата
START_TEST(find_film_res_null)
{
    film_t films[] =
            {
                    { "A", "SomeA", 1990 },
                    { "B", "SomeB", 1991 },
                    { "C", "SomeC", 1992 },
                    { "D", "SomeD", 1993 }
            };

    film_query_t q = { .year = 1990 };

    err_t rc = find_film_binary(films, 4, &q, compare_film_query_year, NULL);

    ck_assert_int_eq(rc, WRONG_DATA);
}
END_TEST

static int cmp_films_by_year(const void *a, const void *b)
{
    return compare_film_year(a, b);
}

/// Write & Read array of films
START_TEST(write_read_films)
{
    film_t films[] =
            {
                    { "A", "SomeA", 1990 },
                    { "B", "SomeB", 1992 },
                    { "C", "SomeC", 1991 },
                    { "D", "SomeD", 1993 }
            };
    size_t n = 4;

    FILE *f = fopen("out/unit_temp.txt", "w");
    ck_assert_ptr_ne(f, NULL);

    print_film_arr(f, films, n);
    fclose(f);

    qsort(films, n, sizeof(film_t), cmp_films_by_year);

    f = fopen("out/unit_temp.txt", "r");
    film_t *new_arr;
    size_t new_len;

    read_film_arr_sorted(f, &new_arr, compare_film_year, &new_len);
    fclose(f);

    ck_assert_int_eq(new_len, n);
    for (size_t i = 0; i < n; i++)
    {
        ck_assert_int_eq(compare_film_year(films + i, new_arr + i), 0);
        ck_assert_int_eq(compare_film_title(films + i, new_arr + i), 0);
        ck_assert_int_eq(compare_film_name(films + i, new_arr + i), 0);
    }
    free_film_arr(new_arr, new_len);
}
END_TEST

Suite *get_field_type_suite()
{
    Suite *s = suite_create("get_field_type");

    TCase *neg = tcase_create("neg");

    tcase_add_test(neg, get_field_wrong);
    tcase_add_test(neg, get_field_empty);

    suite_add_tcase(s, neg);

    TCase *pos = tcase_create("pos");

    tcase_add_test(pos, get_field_title);
    tcase_add_test(pos, get_field_name);
    tcase_add_test(pos, get_field_year);

    suite_add_tcase(s, pos);

    return s;
}

Suite *find_film_binary_suite()
{
    Suite *s = suite_create("find_film_binary");

    TCase *neg = tcase_create("neg");

    tcase_add_test(neg, find_film_arr_null);
    tcase_add_test(neg, find_film_query_null);
    tcase_add_test(neg, find_film_cmp_null);
    tcase_add_test(neg, find_film_res_null);

    suite_add_tcase(s, neg);

    TCase *pos = tcase_create("pos");

    tcase_add_test(pos, find_film_by_name);
    tcase_add_test(pos, find_film_by_name_nf);
    tcase_add_test(pos, find_film_by_title);
    tcase_add_test(pos, find_film_by_title_nf);
    tcase_add_test(pos, find_film_by_year);
    tcase_add_test(pos, find_film_by_year_nf);

    suite_add_tcase(s, pos);

    return s;
}

Suite *complex_test_suite()
{
    Suite *s = suite_create("complex_tests");

    TCase *tcase = tcase_create("io");

    tcase_add_test(tcase, write_read_films);

    suite_add_tcase(s, tcase);

    return s;
}