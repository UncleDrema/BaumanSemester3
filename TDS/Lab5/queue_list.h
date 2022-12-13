//
// Created by archdrema on 11/18/22.
//

#ifndef __QUEUE_LIST_H
#define __QUEUE_LIST_H

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define node_name(type) queue_list_ ## type ## _node_t
#define alloc_node(type) alloc_node_ ## type
#define free_node(type) free_node_ ## type
#define print_var_name(type) print_addr_ ## type

#define list_queue_def(type) queue_def(list, type) \
typedef struct node_name(type)                     \
{                                                  \
    type value;                                    \
    struct node_name(type) *next;\
} node_name(type);                                                  \
struct queue_name(list, type) \
{ \
    node_name(type) *pin;                          \
    node_name(type) *pout;\
};

#define list_queue_impl(type) \
static bool print_var_name(type) = false;\
static node_name(type) *alloc_node(type)(type value) \
{ \
    node_name(type) *mem = malloc(sizeof(node_name(type))); \
    if (mem) \
    { \
        mem->value = value; \
        mem->next = NULL; \
    } \
    return mem; \
} \
static void free_node(type)(node_name(type) *node) \
{ \
    if (node) \
    { \
        free_node(type)(node->next); \
        free(node); \
    } \
} \
queue_name(list, type) *queue_alloc(list, type)() \
{ \
    queue_name(list, type) *mem = malloc(sizeof(queue_name(list, type))); \
    if (mem) \
    { \
        mem->pout = NULL; \
        mem->pin = NULL; \
    } \
    return mem; \
} \
void queue_free(list, type)(queue_name(list, type) *queue) \
{ \
    if (queue) \
    { \
        free_node(type)(queue->pout); \
    } \
} \
err_t queue_enqueue(list, type)(queue_name(list, type) *queue, type value) \
{ \
    if (!queue) \
    { \
        return ERR_DATA; \
    } \
    node_name(type) *node = alloc_node(type)(value); \
    if (print_var_name(type)) printf("enqueue node of addr: %p\n", (void*) node);\
    if (!node) \
    { \
        return ERR_OVERFLOW; \
    } \
    if (!queue->pin) \
    { \
        queue->pin = node; \
        queue->pout = node; \
    } \
    else \
    { \
        queue->pin->next = node; \
        queue->pin = node; \
    } \
    return OK; \
} \
err_t queue_dequeue(list, type)(queue_name(list, type) *queue, type *value) \
{ \
    if (!queue || !value) \
    { \
        return ERR_DATA; \
    } \
    if (!queue->pout) \
    { \
        return ERR_EMPTY; \
    } \
    node_name(type) *out = queue->pout;  \
    if (print_var_name(type)) printf("dequeue node of addr: %p\n", (void*) out); \
    queue->pout = out->next; \
    out->next = NULL; \
    *value = out->value; \
    if (out == queue->pin) \
    { \
        queue->pin = NULL; \
    } \
    free_node(type)(out); \
    return OK; \
} \
size_t queue_len(list, type)(queue_name(list, type) *queue) \
{ \
    if (!queue) \
    { \
        return 0; \
    } \
    size_t size = 0; \
    node_name(type) *cur = queue->pout; \
    while (cur) \
    { \
        size++; \
        cur = cur->next; \
    } \
    return size; \
} \
size_t queue_sizeof(list, type)(queue_name(list, type) *queue) \
{ \
    if (!queue) \
    { \
        return 0; \
    } \
    return (queue_len(list, type)(queue) * (sizeof(node_name(type)*) + sizeof(type))) + 2 * sizeof(node_name(type)*); \
}

#endif
