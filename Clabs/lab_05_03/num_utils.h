#ifndef __NUM_UTILS_H
#define __NUM_UTILS_H
#include <stddef.h>

int to_number_safe(char *str, int *number);

size_t numlen(int number);

int rand_range(int low, int high);

#endif
