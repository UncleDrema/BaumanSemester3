// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/25/22.
// Реализация модульных тестов функции фильтрации

#include <stdlib.h>
#include <check_filter.h>
#include <filter.h>
#include <err.h>

START_TEST(test_filter_pb_src_null_fn)
{
    int *pb_dst;
    int *pe_dst;
    int arr[] = {0, 1, 2, 3};

    int res = key(NULL, arr + 4, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_filter_pe_src_null_fn)
{
    int *pb_dst;
    int *pe_dst;
    int arr[] = {0, 1, 2, 3};

    int res = key(arr, NULL, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_filter_pb_dst_null_fn)
{
    int *pe_dst;
    int arr[] = {0, 1, 2, 3};

    int res = key(arr, arr + 4, NULL, &pe_dst);

    ck_assert_int_eq(res, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_filter_pe_dst_null_fn)
{
    int *pb_dst;
    int arr[] = {0, 1, 2, 3};

    int res = key(arr, arr + 4, &pb_dst, NULL);

    ck_assert_int_eq(res, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_filter_pb_gt_pe_fn)
{
    int *pb_dst;
    int *pe_dst;
    int arr[] = {0, 1, 2, 3};

    int res = key(arr + 4, arr, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_filter_all_remain_fn)
{
    int *pb_dst;
    int *pe_dst;
    int arr[] = {0, 1, 2, 3};
    int arr_res[] = {0, 1, 2, 3};

    int res = key(arr, arr + 4, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, OK);
    ck_assert_ptr_eq(pe_dst, pb_dst + 4);
    ck_assert_mem_eq(pb_dst, arr_res, 4 * sizeof(int));

    free(pb_dst);
}
END_TEST

START_TEST(test_filter_average_fn)
{
    int *pb_dst;
    int *pe_dst;
    int arr[] = {0, 1, -2, 3};
    int arr_res[] = {0, 1};

    int res = key(arr, arr + 4, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, OK);
    ck_assert_ptr_eq(pe_dst, pb_dst + 2);
    ck_assert_mem_eq(pb_dst, arr_res, 2 * sizeof(int));
    free(pb_dst);
}
END_TEST

START_TEST(test_filter_no_remain)
{
    int *pb_dst;
    int *pe_dst;
    int arr[] = {-15, 1, -2, 3};

    int res = key(arr, arr + 4, &pb_dst, &pe_dst);

    ck_assert_int_eq(res, ERR_DATA);
}
END_TEST

START_TEST(test_first_negative_pb_null)
{
    int arr[] = {0, 1, 2, 3};

    int res = get_first_negative_index(NULL, arr + 4);

    ck_assert_int_eq(res, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_first_negative_pe_null)
{
    int arr[] = {0, 1, 2, 3};

    int res = get_first_negative_index(arr, NULL);

    ck_assert_int_eq(res, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_first_negative_pe_lt_pb)
{
    int arr[] = {0, 1, 2, 3};

    int res = get_first_negative_index(arr + 4, arr);

    ck_assert_int_eq(res, ERR_WRONG_ARGS);
}
END_TEST

START_TEST(test_first_negative_no_negative)
{
    int arr[] = {0, 1, 2, 3};

    int res = get_first_negative_index(arr, arr + 4);

    ck_assert_int_eq(res, 4);
}
END_TEST

START_TEST(test_first_negative_average)
{
    int arr[] = {0, 1, -2, 3};

    int res = get_first_negative_index(arr, arr + 4);

    ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(test_first_negative_first)
{
    int arr[] = {-15, 1, -2, 3};

    int res = get_first_negative_index(arr, arr + 4);

    ck_assert_int_eq(res, 0);
}
END_TEST

Suite *first_negative_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("first_negative_index");

    tc_neg = tcase_create("NEG");

    tcase_add_test(tc_neg, test_first_negative_pb_null);
    tcase_add_test(tc_neg, test_first_negative_pe_null);
    tcase_add_test(tc_neg, test_first_negative_pe_lt_pb);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, test_first_negative_no_negative);
    tcase_add_test(tc_pos, test_first_negative_average);
    tcase_add_test(tc_pos, test_first_negative_first);

    suite_add_tcase(s, tc_pos);

    return s;
}

Suite *filter_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("filter (key)");

    tc_neg = tcase_create("NEG");

    tcase_add_test(tc_neg, test_filter_pb_src_null_fn);
    tcase_add_test(tc_neg, test_filter_pe_src_null_fn);
    tcase_add_test(tc_neg, test_filter_pb_dst_null_fn);
    tcase_add_test(tc_neg, test_filter_pe_dst_null_fn);
    tcase_add_test(tc_neg, test_filter_pb_gt_pe_fn);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, test_filter_all_remain_fn);
    tcase_add_test(tc_pos, test_filter_average_fn);
    tcase_add_test(tc_pos, test_filter_no_remain);

    suite_add_tcase(s, tc_pos);

    return s;
}