// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/24/22.
// Реализация основной программы модульного тестирования

#include <check.h>
#include <check_matrix.h>
#include <check_utils.h>

#define OK 0
#define ERR 1

int main(void)
{
    int failed = 0;
    SRunner *runner;

    runner = srunner_create(alloc_suite());
    srunner_add_suite(runner, free_suite());
    srunner_add_suite(runner, add_suite());
    srunner_add_suite(runner, mul_suite());
    srunner_add_suite(runner, det_suite());
    srunner_add_suite(runner, rev_suite());
    srunner_add_suite(runner, float_eq_suite());

    srunner_run_all(runner, CK_VERBOSE);

    failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (failed == 0) ? OK : ERR;
}