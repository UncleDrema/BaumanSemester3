// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 10/28/22.
// Юнит тесты utils.h

#include <check_utils.h>
#include <err.h>
#include <utils.h>

/// Проверка обработки переданной null строки при парсинге числа
START_TEST(stoi_from_null)
{
    err_t rc;
    int res;
    rc = string_to_int(NULL, &res);

    ck_assert_int_eq(rc, NOT_A_NUMBER);
}
END_TEST

/// Проверка обработки переданного null указателя для результата при парсинге числа
START_TEST(stoi_to_null)
{
    err_t rc;
    rc = string_to_int("123", NULL);

    ck_assert_int_eq(rc, NOT_A_NUMBER);
}
END_TEST

/// Проверка обработки переданной некорректной строки при парсинге числа
START_TEST(stoi_nan)
{
    err_t rc;
    int res;
    rc = string_to_int("12bc3", &res);

    ck_assert_int_eq(rc, NOT_A_NUMBER);
}
END_TEST

/// Проверка обработки переданной пустой строки при парсинге числа
START_TEST(stoi_empty)
{
    err_t rc;
    int res;
    rc = string_to_int("", &res);

    ck_assert_int_eq(rc, NOT_A_NUMBER);
}
END_TEST

/// Проверка парсинга положительного числа
START_TEST(stoi_pos)
{
    err_t rc;
    int res;
    rc = string_to_int("123", &res);

    ck_assert_int_eq(res, 123);
    ck_assert_int_eq(rc, OK);
}
END_TEST

/// Проверка парсинга нуля
START_TEST(stoi_zero)
{
    err_t rc;
    int res;
    rc = string_to_int("0", &res);

    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(rc, OK);
}
END_TEST

/// Проверка парсинга множества нулей как одного нуля
START_TEST(stoi_zeros)
{
    err_t rc;
    int res;
    rc = string_to_int("0000", &res);

    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(rc, OK);
}
END_TEST

/// Проверка парсинга отрицательного числа
START_TEST(stoi_neg)
{
    err_t rc;
    int res;
    rc = string_to_int("-123", &res);

    ck_assert_int_eq(res, -123);
    ck_assert_int_eq(rc, OK);
}
END_TEST

Suite *stoi_suite()
{
    Suite *s = suite_create("string to int");

    TCase *neg = tcase_create("neg");

    tcase_add_test(neg, stoi_from_null);
    tcase_add_test(neg, stoi_to_null);
    tcase_add_test(neg, stoi_nan);
    tcase_add_test(neg, stoi_empty);

    suite_add_tcase(s, neg);

    TCase *pos = tcase_create("pos");

    tcase_add_test(pos, stoi_pos);
    tcase_add_test(pos, stoi_zero);
    tcase_add_test(pos, stoi_zeros);
    tcase_add_test(pos, stoi_neg);

    suite_add_tcase(s, pos);

    return s;
}