//
// Created by archdrema on 10/9/22.
//

#include <check_matrix.h>
#include <err.h>
#include <matrix.h>
#include <stdio.h>

// Alloc tests

/// Выделяем память по указателю NULL
START_TEST(alloc_to_null)
{
        err_t rc = alloc_matrix(NULL, 2, 3);

        ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Выделяем матрицу на 0 строк
START_TEST(alloc_zero_rows)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 0, 3);

    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Выделяем матрицу на 0 столбцов
START_TEST(alloc_zero_cols)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 2, 0);

    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Проверяем корректное выделение матрицы
START_TEST(alloc_normal)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 2, 3);
    ck_assert_int_eq(rc, OK);
    free_matrix(&m);
}
END_TEST

// Free tests

/// Проверяем освобождение матрицы на 0 строк
START_TEST(free_zero_rows)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 2, 3);
    ck_assert_int_eq(rc, OK);
    m.rows = 0;
    rc = free_matrix(&m);
    m.rows = 2;
    free_matrix(&m);
    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Проверяем освобождение матрицы на 0 столбцов
START_TEST(free_zero_cols)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 2, 3);
    ck_assert_int_eq(rc, OK);
    m.cols = 0;
    rc = free_matrix(&m);
    m.cols = 3;
    free_matrix(&m);
    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Проверяем освобождение NULL
START_TEST(free_null)
{
    err_t rc = free_matrix(NULL);
    ck_assert_int_eq(rc, OK);
}
END_TEST

/// Проверяем освобождение нормально выделенной матрицы
START_TEST(free_normal)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = free_matrix(&m);
    ck_assert_int_eq(rc, OK);
}
END_TEST

// Add tests

/// Провереяем сложение с NULL
START_TEST(add_null)
{
    matrix_t a;
    matrix_t res;
    err_t rc = alloc_matrix(&a, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = matrix_add(&a, NULL, &res);
    free_matrix(&a);
    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Проверяем запись результата сложения в NULL
START_TEST(add_to_null)
{
    matrix_t a;
    matrix_t b;
    err_t rc = alloc_matrix(&a, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = alloc_matrix(&b, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = matrix_add(&a, &b, NULL);
    free_matrix(&a);
    free_matrix(&b);
    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Проверяем сложение матриц разных размеров
START_TEST(add_not_eq_size)
{
    matrix_t a;
    matrix_t b;
    matrix_t res;
    err_t rc = alloc_matrix(&a, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = alloc_matrix(&b, 3, 3);
    ck_assert_int_eq(rc, OK);
    rc = matrix_add(&a, &b, &res);
    free_matrix(&a);
    free_matrix(&b);
    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Проверяем нормальное сложение двух матриц
START_TEST(add_normal)
{
    matrix_t a;
    matrix_t b;
    matrix_t res;

    size_t rows = 2, cols = 2;

    err_t rc = alloc_matrix(&a, rows, cols);
    ck_assert_int_eq(rc, OK);
    rc = alloc_matrix(&b, rows, cols);
    ck_assert_int_eq(rc, OK);

    a.data[0][0] = 2.0f;
    a.data[0][1] = 1.5f;
    a.data[1][0] = 3.5f;
    a.data[1][1] = 1.75f;

    b.data[0][0] = 0.0f;
    b.data[0][1] = -30.0f;
    b.data[1][0] = 0.11f;
    b.data[1][1] = 1.32f;

    rc = matrix_add(&a, &b, &res);
    ck_assert_int_eq(rc, OK);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            ck_assert_float_eq_tol(res.data[i][j], a.data[i][j] + b.data[i][j], 1e-6f);
        }
    }

    free_matrix(&a);
    free_matrix(&b);
    free_matrix(&res);
}
END_TEST

// Mul tests

/// Проверяем умножение на NULL
START_TEST(mul_null)
{
    matrix_t a;
    matrix_t res;
    err_t rc = alloc_matrix(&a, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = matrix_mul(&a, NULL, &res);
    free_matrix(&a);
    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Проверяем запись результата умножения в NULL
START_TEST(mul_to_null)
{
    matrix_t a;
    matrix_t b;
    err_t rc = alloc_matrix(&a, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = alloc_matrix(&b, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = matrix_mul(&a, &b, NULL);
    free_matrix(&a);
    free_matrix(&b);
    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Проверяем умножение матриц некорректных размеров (столбцы A не равны строкам B)
START_TEST(mul_wrong_size)
{
    matrix_t a;
    matrix_t b;
    matrix_t res;
    err_t rc = alloc_matrix(&a, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = alloc_matrix(&b, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = matrix_mul(&a, &b, &res);
    free_matrix(&a);
    free_matrix(&b);
    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Проверяем умножение с результатом в виде матрицы 1 на 1
START_TEST(mul_size_one)
{
    matrix_t a;
    matrix_t b;
    matrix_t res;
    err_t rc = alloc_matrix(&a, 1, 3);
    ck_assert_int_eq(rc, OK);
    rc = alloc_matrix(&b, 3, 1);
    ck_assert_int_eq(rc, OK);

    a.data[0][0] = 1;
    a.data[0][1] = 2;
    a.data[0][2] = 3;

    b.data[0][0] = 4;
    b.data[1][0] = 5;
    b.data[2][0] = 6;

    /*
     *         4
     * 1 2 3 * 5 = 1*4 + 2*5 + 3+6 = 4 + 10 + 18 = 32
     *         6
     */

    rc = matrix_mul(&a, &b, &res);
    free_matrix(&a);
    free_matrix(&b);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(res.rows, 1);
    ck_assert_int_eq(res.cols, 1);
    ck_assert_float_eq_tol(res.data[0][0], 32, 1e-6f);

    free_matrix(&res);
}
END_TEST

/// Проверяем обычный сценарий умножения
START_TEST(mul_normal)
{
    matrix_t a;
    matrix_t b;
    matrix_t res;
    err_t rc = alloc_matrix(&a, 2, 3);
    ck_assert_int_eq(rc, OK);
    rc = alloc_matrix(&b, 3, 2);
    ck_assert_int_eq(rc, OK);

    a.data[0][0] = 1;
    a.data[1][0] = 1.5f;
    a.data[0][1] = 2;
    a.data[1][1] = 2.5f;
    a.data[0][2] = 3;
    a.data[1][2] = 3.5f;

    b.data[0][0] = 4;
    b.data[0][1] = 4.5f;
    b.data[1][0] = 5;
    b.data[1][1] = 5.5f;
    b.data[2][0] = 6;
    b.data[2][1] = 6.5f;

    /*
     *  1   2   3    4 4.5   32   35
     * 1.5 2.5 3.5 * 5 5.5 = 39.5 43.25
     *               6 6.5
     */

    rc = matrix_mul(&a, &b, &res);
    free_matrix(&a);
    free_matrix(&b);
    ck_assert_int_eq(rc, OK);

    ck_assert_int_eq(res.rows, 2);
    ck_assert_int_eq(res.cols, 2);
    ck_assert_float_eq_tol(res.data[0][0], 32, 1e-6f);
    ck_assert_float_eq_tol(res.data[0][1], 35, 1e-6f);
    ck_assert_float_eq_tol(res.data[1][0], 39.5f, 1e-6f);
    ck_assert_float_eq_tol(res.data[1][1], 43.25f, 1e-6f);

    free_matrix(&res);
}
END_TEST

/// Определитель NULL матрицы
START_TEST(det_null)
{
    matrix_t a;
    err_t rc = alloc_matrix(&a, 1, 1);
    ck_assert_int_eq(rc, OK);

    a.data[0][0] = 5.0f;

    float det;
    rc = get_determinant(NULL, &det);

    free_matrix(&a);

    ck_assert_int_eq(rc, DATA_ERR);
}

/// Запись результата по адресу NULL
START_TEST(det_to_null)
{
    matrix_t a;
    err_t rc = alloc_matrix(&a, 1, 1);
    ck_assert_int_eq(rc, OK);

    a.data[0][0] = 5.0f;

    rc = get_determinant(&a, NULL);

    free_matrix(&a);

    ck_assert_int_eq(rc, DATA_ERR);
}

/// Не квадратная матрица
START_TEST(det_wrong_size)
{
    matrix_t a;
    err_t rc = alloc_matrix(&a, 2, 3);
    ck_assert_int_eq(rc, OK);

    a.data[0][0] = 5.0f;

    float temp;
    rc = get_determinant(&a, &temp);

    free_matrix(&a);

    ck_assert_int_eq(rc, DATA_ERR);
}

/// Определитель матрицы 1 на 1
START_TEST(det_size1)
{
    matrix_t a;
    err_t rc = alloc_matrix(&a, 1, 1);
    ck_assert_int_eq(rc, OK);

    a.data[0][0] = 5.0f;

    float det;
    rc = get_determinant(&a, &det);

    free_matrix(&a);

    ck_assert_int_eq(rc, OK);
    ck_assert_float_eq_tol(det, 5.0f, 1e-6f);
}

/// Определитель матрицы 2 на 2
START_TEST(det_size2)
{
    matrix_t a;
    err_t rc = alloc_matrix(&a, 2, 2);
    ck_assert_int_eq(rc, OK);

    a.data[0][0] = 1;
    a.data[1][0] = 1.5f;
    a.data[0][1] = 2;
    a.data[1][1] = 2.5f;

    /*
     * 1   2
     * 1.5 2.5
     *
     * det = 1 * 2.5 - 1.5 * 2 = 2.5 - 3 = -0.5
     */

    float det;
    rc = get_determinant(&a, &det);

    free_matrix(&a);

    ck_assert_int_eq(rc, OK);
    ck_assert_float_eq_tol(det, -0.5f, 1e-6f);
}

/// Определитель матрицы 4 на 4 (считается через рекурсию, а не через формулу)
START_TEST(det_size4)
{
    matrix_t a;
    err_t rc = alloc_matrix(&a, 4, 4);
    ck_assert_int_eq(rc, OK);

    a.data[0][0] = 1.0f;
    a.data[0][1] = 2.0f;
    a.data[0][2] = 3.0f;
    a.data[0][3] = 0.0f;

    a.data[1][0] = 0.0f;
    a.data[1][1] = -6.5f;
    a.data[1][2] = -7.5f;
    a.data[1][3] = -8.5f;

    a.data[2][0] = 9.0f;
    a.data[2][1] = 10.0f;
    a.data[2][2] = 0.0f;
    a.data[2][3] = 12.0f;

    a.data[3][0] = -13.5f;
    a.data[3][1] = 0.0f;
    a.data[3][2] = -15.5f;
    a.data[3][3] = -16.5f;

    /*
     * Посчитано при помощи интернета
     */

    float det;
    rc = get_determinant(&a, &det);

    free_matrix(&a);

    ck_assert_int_eq(rc, OK);
    ck_assert_float_eq_tol(det, -6882.25f, 1e-6f);
}

/// Исходная матрица - NULL
START_TEST(rev_null)
{
    matrix_t res;
    err_t rc = matrix_rev(NULL, &res);

    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Результат пишем в NULL
START_TEST(rev_to_null)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 2, 2);
    ck_assert_int_eq(rc, OK);

    m.data[0][0] = 1;
    m.data[0][1] = -1;

    m.data[1][0] = 0;
    m.data[1][1] = 2;

    rc = matrix_rev(&m, NULL);

    free_matrix(&m);

    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Не квадратная матрица
START_TEST(rev_wrong_size)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 2, 1);
    ck_assert_int_eq(rc, OK);

    m.data[0][0] = 1;
    m.data[1][0] = 0;

    matrix_t res;
    rc = matrix_rev(&m, &res);

    free_matrix(&m);

    ck_assert_int_eq(rc, DATA_ERR);
}
END_TEST

/// Определитель матрицы равен нулю
START_TEST(rev_det_zero)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 2, 2);
    ck_assert_int_eq(rc, OK);

    m.data[0][0] = 7;
    m.data[0][1] = 0;

    m.data[1][0] = 3;
    m.data[1][1] = 0;

    matrix_t res;
    rc = matrix_rev(&m, &res);

    free_matrix(&m);

    ck_assert_int_eq(rc, ZERO_DET_ERR);
}
END_TEST


/// Считаем обычную обратную матрицу размером 1
START_TEST(rev_size1)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 1, 1);
    ck_assert_int_eq(rc, OK);

    float value = 5.0f;
    m.data[0][0] = value;

    /* matrix
     * 5
     * rev matrix
     * 0.2
     */

    matrix_t res;

    rc = matrix_rev(&m, &res);
    ck_assert_int_eq(rc, OK);

    free_matrix(&m);

    ck_assert_float_eq_tol(res.data[0][0], 1 / value, 1e-6f);

    free_matrix(&res);
}
END_TEST

/// Считаем обычную обратную матрицу размером 2
START_TEST(rev_size2)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 2, 2);
    ck_assert_int_eq(rc, OK);

    m.data[0][0] = 1;
    m.data[0][1] = -1;

    m.data[1][0] = 0;
    m.data[1][1] = 2;

    /* matrix
     *  1 -1
     *  0  2
     * rev matrix
     * 1 0.5
     * 0 0.5
     */

    matrix_t res;

    rc = matrix_rev(&m, &res);
    ck_assert_int_eq(rc, OK);

    free_matrix(&m);

    ck_assert_float_eq_tol(res.data[0][0], 1, 1e-6f);
    ck_assert_float_eq_tol(res.data[0][1], 0.5, 1e-6f);

    ck_assert_float_eq_tol(res.data[1][0], 0, 1e-6f);
    ck_assert_float_eq_tol(res.data[1][1], 0.5, 1e-6f);

    free_matrix(&res);
}
END_TEST

/// Считаем обычную обратную матрицу размером 3
START_TEST(rev_size3)
{
    matrix_t m;
    err_t rc = alloc_matrix(&m, 3, 3);
    ck_assert_int_eq(rc, OK);

    m.data[0][0] = 1;
    m.data[0][1] = 0;
    m.data[0][2] = 0;

    m.data[1][0] = 1;
    m.data[1][1] = -1;
    m.data[1][2] = 0;

    m.data[2][0] = 1;
    m.data[2][1] = 0;
    m.data[2][2] = 1;

    /* matrix
     *  1  0  0
     *  1 -1  0
     *  1  0  1
     * rev matrix
     *  1  0  0
     *  1 -1  0
     * -1  0  1
     */

    matrix_t res;

    rc = matrix_rev(&m, &res);
    ck_assert_int_eq(rc, OK);

    free_matrix(&m);

    ck_assert_float_eq_tol(res.data[0][0], 1, 1e-6f);
    ck_assert_float_eq_tol(res.data[0][1], 0, 1e-6f);
    ck_assert_float_eq_tol(res.data[0][2], 0, 1e-6f);

    ck_assert_float_eq_tol(res.data[1][0], 1, 1e-6f);
    ck_assert_float_eq_tol(res.data[1][1], -1, 1e-6f);
    ck_assert_float_eq_tol(res.data[1][2], 0, 1e-6f);

    ck_assert_float_eq_tol(res.data[2][0], -1, 1e-6f);
    ck_assert_float_eq_tol(res.data[2][1], 0, 1e-6f);
    ck_assert_float_eq_tol(res.data[2][2], 1, 1e-6f);

    free_matrix(&res);
}
END_TEST


Suite *alloc_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("matrix_alloc");

    tc_neg = tcase_create("NEG");
    tcase_add_test(tc_neg, alloc_to_null);
    tcase_add_test(tc_neg, alloc_zero_rows);
    tcase_add_test(tc_neg, alloc_zero_cols);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, alloc_normal);

    suite_add_tcase(s, tc_pos);

    return s;
}

Suite *free_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("matrix_free");

    tc_neg = tcase_create("NEG");
    tcase_add_test(tc_neg, free_null);
    tcase_add_test(tc_neg, free_zero_rows);
    tcase_add_test(tc_neg, free_zero_cols);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, free_normal);

    suite_add_tcase(s, tc_pos);

    return s;
}

Suite *add_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("matrix_add");

    tc_neg = tcase_create("NEG");
    tcase_add_test(tc_neg, add_null);
    tcase_add_test(tc_neg, add_to_null);
    tcase_add_test(tc_neg, add_not_eq_size);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, add_normal);

    suite_add_tcase(s, tc_pos);

    return s;
}

Suite *mul_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("matrix_mul");

    tc_neg = tcase_create("NEG");
    tcase_add_test(tc_neg, mul_null);
    tcase_add_test(tc_neg, mul_to_null);
    tcase_add_test(tc_neg, mul_wrong_size);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, mul_size_one);
    tcase_add_test(tc_pos, mul_normal);

    suite_add_tcase(s, tc_pos);

    return s;
}

Suite *det_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("matrix_get_det");

    tc_neg = tcase_create("NEG");

    tcase_add_test(tc_neg, det_null);
    tcase_add_test(tc_neg, det_wrong_size);
    tcase_add_test(tc_neg, det_to_null);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, det_size1);
    tcase_add_test(tc_pos, det_size2);
    tcase_add_test(tc_pos, det_size4);

    suite_add_tcase(s, tc_pos);

    return s;
}

Suite *rev_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("matrix_rev");

    tc_neg = tcase_create("NEG");

    tcase_add_test(tc_neg, rev_null);
    tcase_add_test(tc_neg, rev_to_null);
    tcase_add_test(tc_neg, rev_wrong_size);
    tcase_add_test(tc_neg, rev_det_zero);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("POS");

    tcase_add_test(tc_pos, rev_size3);
    tcase_add_test(tc_pos, rev_size2);
    tcase_add_test(tc_pos, rev_size1);

    suite_add_tcase(s, tc_pos);

    return s;
}