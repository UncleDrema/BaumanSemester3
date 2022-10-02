// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/20/22.
// Реализация функции сортировки и вспомогательных функций

#include <sort.h>
#include <string.h>

err_t move_to_pos(void *arr, void *from, void *to, size_t len, size_t size)
{
    if (size == 0 || to > from || ((char *) from - ((char *) arr)) / size > len - 1 || ((char *) to - ((char *) arr)) / size > len - 1 || arr == NULL)
    {
        return ERR_WRONG_ARGS;
    }

    if (from == to)
    {
        return OK;
    }

    char char_buf[size];
    void *buf = char_buf;

    memcpy(buf, from, size);
    char *cur_inner, *prev_inner;
    for (cur_inner = from, prev_inner = cur_inner - size; cur_inner > (char *) to; cur_inner -= size, prev_inner -= size)
    {
        memcpy(cur_inner, prev_inner, size);
    }
    memcpy(to, buf, size);

    return OK;
}

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *))
{
    if (number <= 1 || size == 0 || comparator == NULL || first == NULL)
    {
        return;
    }

    char *prev_p = first, *current_p, *end_p;
    for (current_p = prev_p + size, end_p = prev_p + number * size; current_p < end_p; current_p += size, prev_p += size)
    {
        if (comparator(current_p, prev_p) > 0)
        {
            continue;
        }

        char *l_p = first, *r_p = current_p;
        while (l_p < r_p)
        {
            size_t l = (l_p - ((char *) first)) / size;
            size_t r = (r_p - ((char *) first)) / size;
            char *mid = l_p + (((r - l)) / 2) * size;
            int cmp = comparator(current_p, mid);

            if (cmp < 0)
            {
                r_p = mid;
            }
            else
            {
                l_p = mid + size;
            }
        }

        move_to_pos(first, current_p, l_p, number, size);
    }
}

void *at_index(void *arr, size_t index, size_t size)
{
    return ((char *) arr) + (size * index);
}
