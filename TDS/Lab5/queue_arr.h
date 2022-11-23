//
// Created by archdrema on 11/17/22.
//

#ifndef __QUEUE_ARR_H
#define __QUEUE_ARR_H

#define INIT_ARR_SIZE 5

#include "queue.h"
#include <stdlib.h>
#include <string.h>

#define queue_optimize(type) queue_optimize_ ## type
#define queue_enlarge(type) queue_enlarge_ ## type
#define queue_resize(type) queue_resize_ ## type

#define arr_queue_def(type) queue_def(arr, type) \
struct queue_name(arr, type) \
{ \
    type *arr;                                   \
    type *pin;                                   \
    type *pout;                                  \
    type *end;                                   \
};

#define arr_queue_impl(type) \
static err_t queue_optimize(type)(queue_name(arr, type) *queue) \
{ \
    if (!queue) \
    { \
        return ERR_DATA; \
    } \
    if (queue->pout != queue->arr) \
    { \
        size_t diff = queue->pout - queue->arr; \
        memmove(queue->arr, queue->pout, (queue->end - queue->arr) - diff); \
        queue->pout -= diff; \
        queue->pin -= diff; \
    } \
    return OK; \
} \
static err_t queue_resize(type)(queue_name(arr, type) *queue, size_t new_size) \
{ \
    if (!queue) \
    { \
        return ERR_DATA; \
    } \
    type *new_arr = realloc(queue->arr, new_size * sizeof(type)); \
    if (!new_arr) \
    { \
        return ERR_OVERFLOW; \
    } \
    type *prev_arr = queue->arr; \
    queue->arr = new_arr; \
    queue->end = queue->arr + new_size; \
    queue->pin = queue->arr + (queue->pin - prev_arr); \
    queue->pout = queue->arr + (queue->pout - prev_arr); \
    return OK; \
} \
queue_name(arr, type) *queue_alloc(arr, type)() \
{ \
    queue_name(arr, type) *mem = malloc(sizeof(queue_name(arr, type))); \
    if (mem) \
    { \
        mem->arr = calloc(INIT_ARR_SIZE, sizeof(type)); \
        if (mem->arr) \
        { \
            mem->end = mem->arr + INIT_ARR_SIZE; \
            mem->pin = mem->pout = mem->arr; \
        } \
        else \
        { \
            free(mem); \
            mem = NULL; \
        } \
    } \
    return mem; \
} \
err_t queue_enqueue(arr, type)(queue_name(arr, type) *queue, type value) \
{ \
    if (!queue) \
    { \
        return ERR_DATA; \
    } \
    if (queue->pin == queue->end) \
    { \
        queue_optimize(type)(queue); \
        if (queue->pin == queue->end && (queue_resize(type)(queue, queue_len(arr, type)(queue) * 4 / 3) != OK)) \
        { \
            return ERR_OVERFLOW; \
        } \
    } \
    *queue->pin = value; \
    queue->pin++; \
    return OK; \
} \
err_t queue_dequeue(arr, type)(queue_name(arr, type) *queue, type *value) \
{ \
    if (!queue || !value) \
    { \
        return ERR_DATA; \
    } \
    if (queue->pout == queue->pin) \
    { \
        return ERR_EMPTY; \
    } \
    *value = *queue->pout; \
    queue->pout++; \
    return OK; \
} \
void queue_free(arr, type)(queue_name(arr, type) *queue) \
{ \
    if (queue) \
    { \
        free(queue->arr); \
        free(queue); \
    } \
} \
size_t queue_len(arr, type)(queue_name(arr, type) *queue) \
{ \
    if (!queue) \
    { \
        return 0; \
    } \
    return queue->pin - queue->pout; \
} \
size_t queue_sizeof(arr, type)(queue_name(arr, type) *queue) \
{ \
    if (!queue) \
    { \
        return 0; \
    } \
    return (queue->end - queue->arr) * sizeof(type) + 4 * sizeof(type*); \
}

#endif
