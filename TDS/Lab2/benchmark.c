//
// Created by archdrema on 10/1/22.
//

#include "benchmark.h"
#include "sort.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define REPEATS 100000
#define COPY memcpy(arr_copy, init_arr, len * sizeof(book_t)); memcpy(keys_copy, init_keys, len * sizeof(table_key_t))

int book_cmp(const void *a, const void *b)
{
    book_t const *a_real = a;
    book_t const *b_real = b;
    return a_real->page_count - b_real->page_count;
}

int key_cmp(const void *a, const void *b)
{
    table_key_t const *a_real = a;
    table_key_t const *b_real = b;
    return a_real->page_count - b_real->page_count;
}

void benchmark(book_t *init_arr, size_t len)
{
    puts("Starting benchmark...");
    book_t *arr_copy = calloc(len, sizeof(book_t));
    table_key_t *keys_copy = calloc(len, sizeof(table_key_t));

    table_key_t *init_keys = calloc(len, sizeof(table_key_t));

    for (int i = 0; i < len; ++i) {
        init_keys[i].base_table_index = i;
        init_keys[i].page_count = init_arr[i].page_count;
    }

    COPY;

    // Qsort default
    puts("Testing qsort with default sorting...");
    float q_def = 0;
    {
        unsigned long long total = 0, begin, end;

        begin = milliseconds_now();
        for (int i = 0; i < REPEATS; ++i)
        {
            COPY;
            qsort(arr_copy, len, sizeof(book_t), book_cmp);
        }
        end = milliseconds_now();
        total = end - begin;

        q_def = total / ((float) REPEATS);
    }

    // Qsort index
    puts("Testing qsort with key table sorting...");
    float q_ind = 0;
    {
        unsigned long long total = 0, begin, end;

        begin = milliseconds_now();
        for (int i = 0; i < REPEATS; ++i)
        {
            COPY;
            qsort(keys_copy, len, sizeof(table_key_t), key_cmp);
        }
        end = milliseconds_now();
        total = end - begin;

        q_ind = total / ((float) REPEATS);
    }

    // Mysort index
    puts("Testing mysort with key table sorting...");
    float my_ind = 0;
    {
        unsigned long long total = 0, begin, end;

        begin = milliseconds_now();
        for (int i = 0; i < REPEATS; ++i)
        {
            COPY;
            mysort(keys_copy, len, sizeof(table_key_t), key_cmp);
        }
        end = milliseconds_now();
        total = end - begin;

        my_ind = total / ((float) REPEATS);
    }

    puts("----------------------------------------------------------------");
    puts("|        Sort       | Time    | Percent | Memory     | Percent |");
    printf("|  Qsort (default)  | %5.3fms | %3.2f%% | %lu bytes | %3.2f%% |\n", q_def, 100.0, (sizeof(book_t) * len), 100.0);
    printf("|  Qsort (index)    | %5.3fms | %3.2f%% | %lu bytes | %3.2f%%  |\n", q_ind, (q_def / q_ind) * 100, (sizeof(book_t) + sizeof(table_key_t)) * len,  100.0 * ((float)sizeof(book_t)) / (float)(sizeof(book_t) + sizeof(table_key_t)));
    printf("|  Mysort (index)   | %5.3fms | %3.2f%%  | %lu bytes | %3.2f%%  |\n", my_ind, (q_def / my_ind) * 100, (sizeof(book_t) + sizeof(table_key_t)) * len, 100.0 * ((float)sizeof(book_t)) / (float)(sizeof(book_t) + sizeof(table_key_t)));
    puts("----------------------------------------------------------------");

    free(init_keys);
    free(arr_copy);
}

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}