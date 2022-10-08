//
// Created by archdrema on 10/1/22.
//

#ifndef __BENCHMARK_H
#define __BENCHMARK_H

#include "book.h"

int book_cmp(const void *a, const void *b);

int key_cmp(const void *a, const void *b);

void benchmark(book_t *init_arr, size_t len);

unsigned long long milliseconds_now(void);

#endif
