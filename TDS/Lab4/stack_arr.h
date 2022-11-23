//
// Created by archdrema on 11/10/22.
//

#ifndef __STACK_ARR_H
#define __STACK_ARR_H

#include "stack.h"
#include <stdlib.h>

#define INIT_ARR_SIZE 10

#define stack_shrink(type) stack_shrink_ ## type
#define stack_enlarge(type) stack_enlarge_ ## type
#define stack_resize(type) stack_resize_ ## type

#define arr_stack_def(type) stack_def(arr, type) \
                                                \
struct stack_name(arr, type)                     \
{                                                \
    type *arr;                                  \
    type *ps;                                   \
    type *end;                                  \
};

#define arr_stack_impl(type) \
static err_t stack_resize(type)(stack_name(arr, type) *stack, size_t new_size) \
{                            \
    if (!stack)              \
    {                        \
        return ERR_DATA;\
    }                        \
    size_t old_size = stack_len(arr, type)(stack);                             \
    type *new_arr = realloc(stack->arr, new_size * sizeof(type));            \
    if (!new_arr)            \
    {                        \
        return ERR_OVERFLOW;\
    }                        \
    stack->arr = new_arr;    \
    stack->end = stack->arr + new_size;                                        \
    stack->ps = (stack->arr + old_size) - 1;\
    return OK;\
}\
static err_t stack_enlarge(type)(stack_name(arr, type) *stack) \
{\
    return stack_resize(type)(stack, stack_len(arr, type)(stack) * 2);\
}\
stack_name(arr, type) *stack_alloc(arr, type)()    \
{ \
    stack_name(arr, type) *mem = malloc(sizeof(stack_name(arr, type))); \
    if (mem) \
    { \
        mem->arr = calloc(INIT_ARR_SIZE, sizeof(type)); \
        if (mem->arr) \
        { \
            mem->ps = mem->arr - 1; \
            mem->end = mem->arr + INIT_ARR_SIZE; \
        } \
        else \
        { \
            free(mem); \
        } \
    } \
    return mem; \
} \
err_t stack_push(arr, type)(stack_name(arr, type) *stack, type value) \
{ \
    if (!stack) \
    { \
        return ERR_DATA; \
    }                        \
    if (stack->ps + 1 == stack->end && (stack_enlarge(type)(stack) != OK)) \
    {                        \
        return ERR_OVERFLOW; \
    }                        \
    stack->ps++;             \
    *stack->ps = value;      \
    return OK; \
} \
err_t stack_pop(arr, type) (stack_name(arr, type) *stack, type *result) \
{                            \
    if (!stack || !result)   \
    {                        \
        return ERR_DATA;\
    }\
    if (stack->ps < stack->arr) \
    { \
        return ERR_EMPTY; \
    } \
    *result = *stack->ps; \
    stack->ps--; \
    return OK; \
} \
size_t stack_len(arr, type) (stack_name(arr, type) *stack) \
{ \
    if (!stack) \
    { \
        return ERR_DATA; \
    } \
    return (stack->ps - stack->arr) + 1; \
} \
void stack_free(arr, type) (stack_name(arr, type) *stack) \
{ \
    if (stack) \
    { \
        free(stack->arr); \
        free(stack); \
    } \
}                            \
err_t stack_peek(arr, type) (stack_name(arr, type) *stack, type *result)  \
{                            \
    if (!stack || !result)   \
    {                        \
        return ERR_DATA;                         \
    }                        \
    if (stack->ps < stack->arr) \
    { \
        return ERR_EMPTY; \
    } \
    *result = *stack->ps;    \
    return OK;\
}                            \
size_t stack_sizeof(arr, type)(stack_name(arr, type) *stack) \
{ \
    return (stack->end - stack->arr) * sizeof(type*) + 3 * sizeof(type**); \
}                            \
err_t stack_shrink(type) (stack_name(arr, type) *stack)                     \
{   \
    return stack_resize(type)(stack, stack_len(arr, type)(stack)); \
}


#endif
