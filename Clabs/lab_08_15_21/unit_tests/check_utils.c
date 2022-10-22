//
// Created by archdrema on 10/17/22.
//

#include <check_utils.h>
#include <utils.h>

/// Проверка на равенство с высокой точностью
START_TEST(float_eq_eq_small)
{
    ck_assert_int_eq(float_eq(0.00001f, 0.000011f, 0.00001f), 1);
}
END_TEST

/// Проверка на равенство с низкой точностью
START_TEST(float_eq_eq_big)
{
    ck_assert_int_eq(float_eq(0.001f, 0.0011f, 0.001f), 1);
}

/// Проверка на неравенство с высокой точностью
START_TEST(float_eq_ne_small)
{
    ck_assert_int_eq(float_eq(2e-6f, 3e-6f, 1e-7f), 0);
}
END_TEST

/// Проверка на неравенство с высокой точностью
START_TEST(float_eq_ne_big)
{
    ck_assert_int_eq(float_eq(0.001f, 0.003f, 0.001f), 0);
}
END_TEST

Suite *float_eq_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("float_eq");

    tc = tcase_create("test");
    tcase_add_test(tc, float_eq_eq_big);
    tcase_add_test(tc, float_eq_ne_small);
    tcase_add_test(tc, float_eq_ne_big);
    tcase_add_test(tc, float_eq_eq_small);

    suite_add_tcase(s, tc);

    return s;
}
