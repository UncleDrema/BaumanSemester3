#ifndef __BINARY_IO_H
#define __BINARY_IO_H
#include <stdio.h>

int get_number_by_pos(FILE *f, int index);

void put_number_by_pos(FILE *f, int index, int number);

int get_number_count(FILE *f);

#endif
