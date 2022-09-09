//
// Created by archdrema on 7/24/22.
//

#include "stdbool.h"
#ifndef LAB1_UTILS_H
#define LAB1_UTILS_H

#define NOT_FOUND -1

#define to_char(digit) ((char) ((digit) + '0'))
#define to_int(digit) ((int) digit - '0')

int firstNotEqual(const int *arr, int len, int val);

int firstNotEqualFromEnd(const int *arr, int len, int val);

bool all_equal(const int* arr, int len, int value);

void shiftLeft(int *arr, int len);

void shiftRight(int *arr, int len);

void cycleShiftLeft(int *arr, int len);

void cycleShiftRight(int *arr, int len);

#endif //LAB1_UTILS_H
