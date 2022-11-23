//
// Created by archdrema on 11/10/22.
//

#ifndef __STACK_LIST_H
#define __STACK_LIST_H

#include <stdlib.h>
#include "stack.h"

#define node_name(type) stack_list_ ## type ## _node_t
#define alloc_node(type) alloc_node_ ## type
#define free_node(type) free_node_ ## type
#define push_node(type) push_node_ ## type

#define list_stack_def(type) stack_def(list, type) \
typedef struct node_name(type) \
{ \
    type value; \
    struct node_name(type) *prev; \
} node_name(type); \
struct stack_name(list, type) \
{ \
    node_name(type) *top; \
};

#define list_stack_impl(type) \
static node_name(type) *alloc_node(type)() \
{ \
    node_name(type) *node = malloc(sizeof(node_name(type))); \
    if (node) \
    { \
        node->prev = NULL; \
    } \
    return node; \
}                             \
static void free_node(type)(node_name(type) *node)           \
{                             \
    if (node)                 \
    {                         \
        free_node(type)(node->prev);\
        free(node);\
    }\
}\
stack_name(list, type) *stack_alloc(list, type)() \
{ \
    stack_name(list, type) *mem = malloc(sizeof(stack_name(list, type))); \
    if (mem) \
    { \
        mem->top = NULL; \
    } \
    return mem; \
} \
void stack_free(list, type)(stack_name(list, type) *stack) \
{ \
    if (stack) \
    {                         \
        free_node(type)(stack->top);\
        free(stack); \
    } \
}                             \
static err_t push_node(type)(stack_name(list, type) *stack, node_name(type) *node) \
{                             \
    if (!stack || !node)   \
    {                         \
        return ERR_DATA;\
    }                         \
    node->prev = stack->top;  \
    stack->top = node;        \
    return OK;\
}\
err_t stack_push(list, type)(stack_name(list, type) *stack, type element) \
{ \
    if (!stack) \
    { \
        return ERR_DATA; \
    } \
    node_name(type) *new_top = alloc_node(type)(); \
    if (!new_top) \
    { \
        return ERR_OVERFLOW; \
    } \
    new_top->value = element; \
    new_top->prev = stack->top; \
    stack->top = new_top; \
    return OK; \
} \
err_t stack_pop(list, type)(stack_name(list, type) *stack, type *result) \
{ \
    if (!stack || !result) \
    { \
        return ERR_DATA; \
    } \
    if (stack->top == NULL) \
    { \
        return ERR_EMPTY; \
    } \
    node_name(type) *old_top = stack->top; \
    *result = old_top->value; \
    stack->top = old_top->prev;            \
    old_top->prev = NULL;\
    free_node(type)(old_top); \
    return OK; \
} \
size_t stack_len(list, type) (stack_name(list, type) *stack) \
{ \
    if (!stack) \
    { \
        return ERR_DATA; \
    } \
    size_t count = 0; \
    node_name(type) *node = stack->top; \
    while (node != NULL) \
    { \
        count++; \
        node = node->prev; \
    } \
    return count; \
}                             \
err_t stack_peek(list, type) (stack_name(list, type) *stack, type *result) \
{ \
    if (!stack || !result) \
    { \
        return ERR_DATA; \
    } \
    if (stack->top == NULL) \
    { \
        return ERR_EMPTY; \
    } \
    *result = stack->top->value; \
    return OK; \
}                             \
size_t stack_sizeof(list, type)(stack_name(list, type) *stack) \
{ \
    return (1 + stack_len(list, type)(stack)) * sizeof(node_name(type));\
}

#endif
