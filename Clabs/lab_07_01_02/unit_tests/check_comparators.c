// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/25/22.
// Реализация модульных тестов компараторов

#include <check_comparators.h>
#include <comparators.h>

START_TEST(test_int_eq)
{
    int a = 5;
    int b = 5;

    ck_assert_int_eq(int_comparator(&a, &b), 0);
}

START_TEST(test_int_lt)
{
    int a = 5;
    int b = 17;

    ck_assert_int_lt(int_comparator(&a, &b), 0);
}

START_TEST(test_int_gt)
{
    int a = 5;
    int b = -13;

    ck_assert_int_gt(int_comparator(&a, &b), 0);
}

START_TEST(test_double_eq)
{
    double a = 5.32;
    double b = 5.32;

    ck_assert_int_eq(double_comparator(&a, &b), 0);
}

START_TEST(test_double_lt)
{
    double a = 5.123;
    double b = 17.152;

    ck_assert_int_lt(double_comparator(&a, &b), 0);
}

START_TEST(test_double_gt)
{
    double a = 5.91;
    double b = -13.001;

    ck_assert_int_gt(double_comparator(&a, &b), 0);
}

Suite *comparators_suite(void)
{
    Suite *s;
    TCase *tc_int;
    TCase *tc_double;

    s = suite_create("comparators");

    tc_int = tcase_create("int");

    tcase_add_test(tc_int, test_int_eq);
    tcase_add_test(tc_int, test_int_lt);
    tcase_add_test(tc_int, test_int_gt);

    suite_add_tcase(s, tc_int);

    tc_double = tcase_create("double");

    tcase_add_test(tc_double, test_double_eq);
    tcase_add_test(tc_double, test_double_lt);
    tcase_add_test(tc_double, test_double_gt);

    suite_add_tcase(s, tc_double);

    return s;
}