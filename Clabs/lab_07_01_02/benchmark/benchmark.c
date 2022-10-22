//
// Created by archdrema on 9/25/22.
//

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <sort.h>
#include <err.h>
#include <comparators.h>
#include <old_sort.h>

#define DECL_NAMED_FUNC_T(func_t) typedef struct \
{ \
    char name[16]; \
    func_t func; \
} named_##func_t;
#define PROVIDER_N 3

typedef void (*sort_func)(void *, size_t, size_t, int(*)(const void *, const void *));

DECL_NAMED_FUNC_T(sort_func)

typedef int (*value_provider)(size_t index);

DECL_NAMED_FUNC_T(value_provider)

typedef struct
{
    size_t min;
    size_t max;
    size_t step;
} range_t;

int is_valid(range_t *range);

unsigned long long milliseconds_now(void);

int rand_range(int min, int max);

void init_array(int *arr, size_t size, value_provider provider);

double measure(size_t size, size_t times, sort_func func, value_provider provider);

int good(size_t index);

int bad(size_t index);

int average(size_t index);

int main(int argc, char *argv[])
{
    int rc = OK;
    if (argc != 3)
    {
        rc = ERR_WRONG_ARGS;
    }
    else
    {
        range_t size_range, times_range;
        if (sscanf(argv[1], "%zu:%zu:%zu", &size_range.min, &size_range.max, &size_range.step) == 3 &&
            sscanf(argv[2], "%zu:%zu:%zu", &times_range.min, &times_range.max, &times_range.step) == 3 &&
            is_valid(&size_range) && is_valid(&times_range))
        {
            named_sort_func qsort_named = { "qsort", qsort };
            named_sort_func mysort_named = { "mysort", mysort };
            named_sort_func old_mysort_named = { "old_mysort", old_mysort };
            named_value_provider providers[PROVIDER_N] = { { "good", good }, { "bad", bad }, { "average", average } };

            double mysort_time, qsort_time, old_mysort_time;

            puts("[");
            for (size_t iprov = 0; iprov < PROVIDER_N; iprov++)
                for (size_t isize = size_range.min; isize <= size_range.max; isize += size_range.step)
                {
                    for (size_t itimes = times_range.min; itimes <= times_range.max; itimes += times_range.step)
                    {
                        mysort_time = measure(isize, itimes, mysort_named.func, providers[iprov].func);
                        qsort_time = measure(isize, itimes, qsort_named.func, providers[iprov].func);
                        old_mysort_time = measure(isize, itimes, old_mysort_named.func, providers[iprov].func);

                        printf("    {\n        \"size\": %zu,\n        \"times\": %zu,\n        \"case\": \"%s\",\n        \"results\":\n        {\n            \"mysort\": %.8f,\n            \"qsort\": %.8f,\n            \"old_mysort\": %.8f\n        }\n    }", isize, itimes, providers[iprov].name, mysort_time, qsort_time, old_mysort_time);

                        if (times_range.step == 0)
                        {
                            if (isize + size_range.step <= size_range.max || iprov != PROVIDER_N - 1)
                            {
                                puts(",");
                            }
                            break;
                        }

                        if ((itimes + times_range.step <= times_range.max || isize + size_range.step <= size_range.max) || iprov != PROVIDER_N - 1)
                        {
                            puts(",");
                        }
                    }

                    if (size_range.step == 0)
                    {
                        break;
                    }
                }

            puts("");
            puts("]");
        }
        else
        {
            rc = ERR_WRONG_ARGS;
        }
    }

    return rc;
}

double measure(size_t size, size_t times, sort_func func, value_provider provider)
{
    unsigned long long begin, end, total = 0;
    int *arr = malloc(size * sizeof(int));

    for (size_t i = 0; i < times; i++)
    {
        init_array(arr, size, provider);
        begin = milliseconds_now();
        func(arr, size, sizeof(int), int_comparator);
        end = milliseconds_now();
        total += end - begin;
    }

    return total / ((double) times);
}

unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

int rand_range(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void init_array(int *arr, size_t size, value_provider provider)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = provider(i);
    }
}

int is_valid(range_t *range)
{
    return ((range->min == range->max) && range->step == 0) || ((range->min < range->max) && range->step > 0);
}

int good(size_t index)
{
    return (int)index;
}

int bad(size_t index)
{
    return -(int)index;
}

int average(size_t index)
{
    (void) index;
    return rand_range(-10000, 10000);
}
