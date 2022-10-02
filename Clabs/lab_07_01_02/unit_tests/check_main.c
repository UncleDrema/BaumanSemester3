// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/24/22.
// Реализация основной программы модульного тестирования

#include <check_sort.h>
#include <check_comparators.h>
#include <check_filter.h>
#include <check.h>

#define OK 0
#define ERR 1

int main(void)
{
    int failed = 0;
    SRunner *runner;

    runner = srunner_create(mysort_suite());
    srunner_add_suite(runner, move_to_pos_suite());
    srunner_add_suite(runner, at_index_suite());

    srunner_add_suite(runner, comparators_suite());

    srunner_add_suite(runner, filter_suite());
    srunner_add_suite(runner, first_negative_suite());

    srunner_run_all(runner, CK_VERBOSE);

    failed = srunner_ntests_failed(runner);

    srunner_free(runner);

    return (failed == 0) ? OK : ERR;
}