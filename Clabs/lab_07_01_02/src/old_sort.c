//
// Created by archdrema on 10/16/22.
//

#include "old_sort.h"
#include <string.h>

err_t old_move_to_pos(void *arr, size_t from, size_t to, size_t len, size_t size)
{
    if (to > from || from > len - 1 || to > len - 1 || arr == NULL || size == 0)
    {
        return ERR_WRONG_ARGS;
    }

    if (from == to)
    {
        return OK;
    }

    char char_buf[size];
    void *buf = char_buf;

    void *elem = old_at_index(arr, from, size);
    memcpy(buf, elem, size);
    for (size_t j = from; j > to; j--)
    {
        char *cur_inner = old_at_index(arr, j, size);
        char *prev_inner = old_at_index(arr, j - 1, size);
        memcpy(cur_inner, prev_inner, size);
    }
    memcpy(old_at_index(arr, to, size), buf, size);

    return OK;
}

void old_mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *))
{
    if (number <= 1 || size == 0 || comparator == NULL || first == NULL)
    {
        return;
    }

    for (size_t i = 1; i < number; i++)
    {
        void *cur = old_at_index(first, i, size);
        if (comparator(cur, old_at_index(first, i - 1, size)) > 0)
        {
            continue;
        }

        size_t l = 0, r = i;

        while (l < r)
        {
            size_t mid = l + (r - l) / 2;
            void *mid_value = old_at_index(first, mid, size);
            int cmp = comparator(cur, mid_value);

            if (cmp < 0)
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }

        old_move_to_pos(first, i, l, number, size);
    }
}

void *old_at_index(void *arr, size_t index, size_t size)
{
    return ((char *) arr) + (size * index);
}
