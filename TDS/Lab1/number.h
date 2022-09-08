//
// Created by archdrema on 7/24/22.
//

#ifndef LAB1_NUMBER_H
#define LAB1_NUMBER_H

#include "sign.h"
#include <stdbool.h>

#define MANTISSA_L 30
#define EXPONENT_L 5
#define ERR_IO -1

#define abs_compare(type, a, b) abs_compare_##type(a, b)
#define abs_sub(type, a, b, res) abs_sub_##type(a, b, res)
#define abs_add(type, a, b, res) abs_add_##type(a, b, res)
#define add(type, a, b, res) add_##type(a, b, res)
#define sub(type, a, b, res) sub_##type(a, b, res)
#define copy(type, from, to) copy_##type(from, to, true)

#define def_long_num(len, name) typedef struct { sign_t sign; int value[len]; } name;   \
int abs_compare_##name(name *a, name *b);                                               \
void abs_sub_##name(name a, name b, name *res);                                         \
void abs_add_##name(name a, name b, name *res);                                         \
err_t add_##name(name a, name b, name *res);                                            \
err_t sub_##name(name a, name b, name *res);                                            \
void copy_##name(name *from, name* to, bool copySign);

#define impl_long_num(len, name) \
err_t add_##name(name a, name b, name *result)                                          \
{ \
    if (a.sign != b.sign) \
    { \
        if (abs_compare_##name(&a, &b) >= 0) \
        { \
            abs_sub_##name(a, b, result); \
            result->sign = a.sign; \
        } \
        else \
        { \
            abs_sub_##name(b, a, result); \
            result->sign = b.sign; \
        } \
    } \
    else \
    { \
        result->sign = a.sign; \
        abs_add_##name(a, b, result); \
    } \
    err_t res = OK; \
    if (result->value[0] >= 10 || result->value[0] < 0) \
    { \
        res = OVERFLOW; \
        if (result->value[0] >= 10) \
        { \
            result->value[0] %= 10; \
        } \
        else \
        { \
            while (result->value[0] < 0) \
                result->value[0] += 10; \
        } \
    } \
    return res; \
} \
err_t sub_##name(name a, name b, name *res) \
{ \
    b.sign = MINUS * b.sign; \
    return add_##name(a, b, res);                                                              \
} \
void abs_add_##name(name a, name b, name *result) \
{ \
    for (int i = len - 1; i > 0; i--) { \
        a.value[i] += b.value[i]; \
        while (a.value[i] >= 10) \
        { \
            a.value[i - 1]++; \
            a.value[i] -= 10; \
        } \
    } \
    copy_##name(&a, result, false); \
} \
void abs_sub_##name(name a, name b, name *result) \
{ \
    for (int i = len - 1; i > 0; i--) { \
        a.value[i] -= b.value[i]; \
        while (a.value[i] < 0) \
        { \
            a.value[i - 1]--; \
            a.value[i] += 10; \
        } \
    } \
    copy_##name(&a, result, false); \
} \
void copy_##name(name *from, name *to, bool copySign) \
{ \
    if (copySign) \
    { \
        to->sign = from->sign; \
    } \
    for (int i = 0; i < len; ++i) { \
        to->value[i] = from->value[i]; \
    } \
} \
int abs_compare_##name(name *a, name *b) \
{ \
    int res = 0; \
    for (int i = 0; i < len && res == 0; ++i) { \
        res = a->value[i] - b->value[i]; \
    } \
    return res; \
}

typedef enum {
    OK = 0,
    OVERFLOW = 1,
    EMPTY_INPUT = 2,
    END_TOO_SOON = 3,
    WRONG_START = 4,
    WRONG_AFTER_M_SIGN = 5,
    WRONG_BEFORE_POINT = 6,
    WRONG_AFTER_POINT = 7,
    WRONG_AFTER_MNT_READY = 8,
    WRONG_AFTER_EXP_CHAR = 9,
    WRONG_AFTER_E_SIGN = 10,
    WRONG_EXPONENT = 11,
    OTHER
} err_t;

def_long_num(MANTISSA_L, mantissa_t)
def_long_num(EXPONENT_L, exponent_t)

typedef struct {
    mantissa_t mantissa;
    exponent_t exponent;
} real_t;

void print_real(FILE *f, real_t *num);

static err_t normalize(real_t *num);

err_t input_num(FILE *f, real_t *num);

#endif //LAB1_NUMBER_H
