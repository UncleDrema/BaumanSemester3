//
// Created by archdrema on 11/10/22.
//

#ifndef __STACK_H
#define __STACK_H

#include "err.h"
#include <stddef.h>

#define stack_name(subname, type) stack_ ## subname ## _ ## type ## _t
#define stack_push(subname, type)  stack_push_ ## subname ## _ ## type ## _t
#define stack_pop(subname, type)  stack_pop_ ## subname ## _ ## type ## _t
#define stack_alloc(subname, type)  stack_alloc_ ## subname ## _ ## type ## _t
#define stack_len(subname, type)  stack_len_ ## subname ## _ ## type ## _t
#define stack_free(subname, type)  stack_free_ ## subname ## _ ## type ## _t
#define stack_peek(subname, type) stack_peek_ ## subname ## _ ## type ## _t
#define stack_sizeof(subname, type) stack_sizeof_ ## subname ## _ ## type ## _t

#define stack_def(subname, type) \
typedef struct stack_name(subname, type) stack_name(subname, type);\
                                 \
err_t stack_push(subname, type) (stack_name(subname, type) *stack, type element); \
err_t stack_pop(subname, type) (stack_name(subname, type) *stack, type *result);   \
stack_name(subname, type) *stack_alloc(subname, type)();                           \
size_t stack_len(subname, type) (stack_name(subname, type) *stack);\
void stack_free(subname, type)(stack_name(subname, type) *stack);  \
err_t stack_peek(subname, type)(stack_name(subname, type) *stack, type *result); \
size_t stack_sizeof(subname, type)(stack_name(subname, type) *stack);

#endif
