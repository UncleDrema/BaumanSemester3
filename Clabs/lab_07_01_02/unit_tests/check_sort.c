// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/21/22.
// Реализация модульных тестов функции сортировки и вспомогательных функций

#include <sort.h>
#include <err.h>
#include <comparators.h>
#include <check_sort.h>
#include <check.h>
#include <stdio.h>


START_TEST(test_move_to_bigger_than_from)
{
    err_t rc;
    int arr[3] = {1, 2, 3};

    rc = move_to_pos(arr, arr + 1, arr + 2, 3, sizeof(int));

    ck_assert_int_eq(rc, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_move_too_big_from)
{
    err_t rc;
    int arr[3] = {1, 2, 3};

    rc = move_to_pos(arr, arr + 3, arr + 2, 3, sizeof(int));

    ck_assert_int_eq(rc, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_move_null_arr)
{
    err_t rc;

    int arr[6] = {1, 2, 3, 4, 5, 6};
    rc = move_to_pos(NULL, arr + 5, arr, 10, sizeof(int));

    ck_assert_int_eq(rc, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_move_null_size)
{
    err_t rc;
    int arr[3] = {1, 2, 3};

    rc = move_to_pos(arr, arr + 2, arr, 3, 0);

    ck_assert_int_eq(rc, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_move_int_first)
{
    err_t rc;
    int arr_res[3] = {4, 1, 2};
    int arr[3] = {1, 2, 4};

    rc = move_to_pos(arr, arr + 2, arr, 3, sizeof(int));


    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, arr_res, 3 * sizeof(int));
}
END_TEST

START_TEST(test_move_char_mid)
{
    err_t rc;
    char arr_res[5] = {'l', 'o', 'O', 'o', 'l'};
    char arr[5] = {'l', 'o', 'o', 'O', 'l'};

    rc = move_to_pos(arr, arr + 3, arr + 2, 5, sizeof(char));

    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, arr_res, 5 * sizeof(char));
}
END_TEST

START_TEST(test_move_double_last)
{
    err_t rc;
    double arr_res[3] = {0.5f, 0.025f, 1.0f};
    double arr[3] = {0.5f, 0.025f, 1.0f};

    rc = move_to_pos(arr, arr + 2, arr + 2, 3, sizeof(double));

    ck_assert_int_ne(rc, ERR_WRONG_ARGS);
    ck_assert_mem_eq(arr, arr_res, 3 * sizeof(double));
}
END_TEST

START_TEST(test_sort_null_comparator)
{
    int arr[] = {5, 3, 4, 1, 2};
    int arr_res[] = {5, 3, 4, 1, 2};

    mysort(arr, 5, sizeof(int), NULL);

    ck_assert_mem_eq(arr, arr_res, 5 * sizeof(int));
}
END_TEST

START_TEST(test_sort_null_size)
{
    int arr[] = {5, 3, 4, 1, 2};
    int arr_res[] = {5, 3, 4, 1, 2};

    mysort(arr, 5, 0, int_comparator);

    ck_assert_mem_eq(arr, arr_res, 5 * sizeof(int));
}
END_TEST

START_TEST(test_sort_good_case)
{
    int arr[5] = {1, 2, 3, 4, 5};
    int arr_res[5] = {1, 2, 3, 4, 5};

    mysort(arr, 5, sizeof(int), int_comparator);

    ck_assert_mem_eq(arr, arr_res, 5 * sizeof(int));
}
END_TEST

START_TEST(test_sort_bad_case)
{
    int arr[5] = {5, 4, 3, 2, 1};
    int arr_res[5] = {1, 2, 3, 4, 5};

    mysort(arr, 5, sizeof(int), int_comparator);

    ck_assert_mem_eq(arr, arr_res, 5 * sizeof(int));
}
END_TEST

START_TEST(test_sort_mid_case_double)
{
    double arr[3] = {1.2, -3.1, 0.323};
    double arr_res[3] = {-3.1, 0.323, 1.2};

    mysort(arr, 3, sizeof(double), double_comparator);

    ck_assert_mem_eq(arr, arr_res, 3 * sizeof(double));
}
END_TEST

START_TEST(test_at_index_null_size)
{
    int arr[] = {5, 4, 3, 2, 1};

    void *el = at_index(arr, 2, 0);

    ck_assert_ptr_eq(&arr[0], el);
}
END_TEST

START_TEST(test_at_index_first)
{
    int arr[] = {5, 4, 3, 2, 1};

    void *el = at_index(arr, 0, sizeof(int));

    ck_assert_ptr_eq(&arr[0], el);
}
END_TEST

START_TEST(test_at_index_last)
{
    char arr[] = {5, 4, 3, 2, 1};

    void *el = at_index(arr, 4, sizeof(char));

    ck_assert_ptr_eq(&arr[4], el);
}
END_TEST

START_TEST(test_at_index_mid)
{
    double arr[] = {5, 4, 3, 2, 1};

    void *el = at_index(arr, 2, sizeof(double));

    ck_assert_ptr_eq(&arr[2], el);
}
END_TEST

Suite *move_to_pos_suite(void) {
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("move_to_pos");

    tc_neg = tcase_create("NEG");
    tcase_add_test(tc_neg, test_move_too_big_from);
    tcase_add_test(tc_neg, test_move_to_bigger_than_from);
    tcase_add_test(tc_neg, test_move_null_arr);
    tcase_add_test(tc_neg, test_move_null_size);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");
    tcase_add_test(tc_pos, test_move_int_first);
    tcase_add_test(tc_pos, test_move_char_mid);
    tcase_add_test(tc_pos, test_move_double_last);

    suite_add_tcase(s, tc_pos);

    return s;
}

Suite *mysort_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("mysort");

    tc_neg = tcase_create("NEG");

    tcase_add_test(tc_neg, test_sort_null_size);
    tcase_add_test(tc_neg, test_sort_null_comparator);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, test_sort_good_case);
    tcase_add_test(tc_pos, test_sort_mid_case_double);
    tcase_add_test(tc_pos, test_sort_bad_case);

    suite_add_tcase(s, tc_pos);

    return s;
}

Suite *at_index_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("at_index");

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, test_at_index_first);
    tcase_add_test(tc_pos, test_at_index_mid);
    tcase_add_test(tc_pos, test_at_index_last);
    tcase_add_test(tc_pos, test_at_index_null_size);

    suite_add_tcase(s, tc_pos);

    return s;
}