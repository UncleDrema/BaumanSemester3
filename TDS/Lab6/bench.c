//
// Created by archdrema on 11/11/22.
//

#include "bench.h"
#include <stdlib.h>

struct ms_clock_t
{
    ms_t start;
    ms_t total;
};

ms_t ms_now(void)
{
    struct timeval val;
    if (gettimeofday(&val, NULL))
    {
        return (ms_t)-1;
    }

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

double mean_ms(ms_t total_ms, size_t count)
{
    return ((double) total_ms) / (double) count;
}

ms_clock_t *get_clock(void)
{
    ms_clock_t *clock = malloc(sizeof(ms_clock_t));
    clock->start = 0;
    clock->total = 0;
    return clock;
}

void free_clock(ms_clock_t *clock)
{
    if (clock)
    {
        free(clock);
    }
}

void clock_start(ms_clock_t *clock)
{
    clock->start = ms_now();
}

void clock_stop(ms_clock_t *clock)
{
    ms_t now = ms_now();
    clock->total += (now - clock->start);
    clock->start = now;
}

void clock_reset(ms_clock_t *clock)
{
    clock->total = 0;
    clock->start = 0;
}

ms_t clock_total(ms_clock_t *clock)
{
    return clock->total;
}