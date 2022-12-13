//
// Created by archdrema on 11/17/22.
//

#ifndef __TIME_UTILS_H
#define __TIME_UTILS_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int skip_to_nl(FILE *f);

char *str_without_repeating(const char *str);

char *rand_str(size_t size);

size_t count_str(char *str, char ch, size_t *cmp_count);

#endif
