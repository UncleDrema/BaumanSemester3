//
// Created by archdrema on 11/11/22.
//

#ifndef __BENCH_H
#define __BENCH_H

#include <sys/time.h>
#include <stddef.h>

typedef unsigned long long ms_t;

typedef struct ms_clock_t ms_clock_t;

ms_t ms_now(void);

double mean_ms(ms_t total_ms, size_t count);

ms_clock_t *get_clock(void);

void free_clock(ms_clock_t *clock);

void clock_start(ms_clock_t *clock);

void clock_stop(ms_clock_t *clock);

void clock_reset(ms_clock_t *clock);

ms_t clock_total(ms_clock_t *clock);

#endif
