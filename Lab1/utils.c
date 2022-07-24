//
// Created by archdrema on 7/24/22.
//

#include <stdio.h>
#include "utils.h"

int firstNotEqual(const int *arr, int len, int val)
{
    int i = 0;
    while (i < len && arr[i] == val)
        i++;

    return i == len ? NOT_FOUND : i;
}

int firstNotEqualFromEnd(const int *arr, int len, int val)
{
    int i = len - 1;
    while (i >= 0 && arr[i] == val)
        i--;

    return i;
}

void cycleShiftLeft(int *arr, int len)
{
    int fst = arr[0];
    for (int i = 0; i < len - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    arr[len - 1] = fst;
}

void cycleShiftRight(int *arr, int len)
{
    int lst = arr[len - 1];
    for (int i = len - 1; i > 0; i--)
    {
        arr[i] = arr[i - 1];
    }

    arr[0] = lst;
}

bool all_equal(const int* arr, int len, int value)
{
    for (int i = 0; i < len; ++i) {
        if (arr[i] != value)
            return false;
    }

    return true;
}