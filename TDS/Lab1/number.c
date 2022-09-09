// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 7/24/22.
//

#include <ctype.h>
#include "number.h"
#include "utils.h"
#define LF '\n'

impl_long_num(MANTISSA_L, mantissa_t)

impl_long_num(EXPONENT_L, exponent_t)

impl_long_num(EXPONENT_LARGE_L, exponent_large_t)

impl_long_num(MANTISSA_LARGE_L, mantissa_large_t)

void print_real(FILE *f, real_t *num)
{
    print_sign(f, num->mantissa.sign);
    fprintf(f, "0.");

    int start = firstNotEqualFromEnd(num->mantissa.value, MANTISSA_L, 0);

    if (start == NOT_FOUND)
    {
        putc('0', f);
    }
    else
    {
        for (int i = 0; i <= start; i++)
        {
            putc(to_char(num->mantissa.value[i]), f);
        }
    }

    fprintf(f, " E ");
    print_sign(f, num->exponent.sign);

    int firstNotZero = firstNotEqual(num->exponent.value, EXPONENT_L, 0);

    if (firstNotZero == NOT_FOUND)
    {
        putc('0', f);
    }
    else
    {
        for (int i = firstNotZero; i < EXPONENT_L; ++i)
        {
            putc(to_char(num->exponent.value[i]), f);
        }
    }
}

void print_real_inner(FILE *f, real_inner_t *num)
{
    print_sign(f, num->mantissa.sign);
    fprintf(f, " 0.");

    int start = firstNotEqualFromEnd(num->mantissa.value, MANTISSA_LARGE_L, 0);

    if (start == NOT_FOUND)
    {
        putc('0', f);
    }
    else
    {
        for (int i = 0; i <= start; i++)
        {
            putc(to_char(num->mantissa.value[i]), f);
        }
    }

    fprintf(f, " E ");
    print_sign(f, num->exponent.sign);
    putc(' ', f);

    int firstNotZero = firstNotEqual(num->exponent.value, EXPONENT_LARGE_L, 0);

    if (firstNotZero == NOT_FOUND)
    {
        putc('0', f);
    }
    else
    {
        for (int i = firstNotZero; i < EXPONENT_LARGE_L; ++i)
        {
            putc(to_char(num->exponent.value[i]), f);
        }
    }
}

void print_real_input(FILE *f, real_input_t *num)
{
    print_sign(f, num->mantissa.sign);
    fprintf(f, " 0.");

    int start = firstNotEqualFromEnd(num->mantissa.value, MANTISSA_L, 0);

    if (start == NOT_FOUND)
    {
        putc('0', f);
    }
    else
    {
        for (int i = 0; i <= start; i++)
        {
            putc(to_char(num->mantissa.value[i]), f);
        }
    }

    fprintf(f, " E ");
    print_sign(f, num->exponent.sign);
    putc(' ', f);

    int firstNotZero = firstNotEqual(num->exponent.value, EXPONENT_LARGE_L, 0);

    if (firstNotZero == NOT_FOUND)
    {
        putc('0', f);
    }
    else
    {
        for (int i = firstNotZero; i < EXPONENT_LARGE_L; ++i)
        {
            putc(to_char(num->exponent.value[i]), f);
        }
    }
}

static err_t normalize(real_input_t *num)
{
    err_t res;
    int notZero = firstNotEqual(num->mantissa.value, MANTISSA_L, 0);

    //cppcheck-suppress legacyUninitvar
    exponent_large_t sub_exp = {MINUS, {[EXPONENT_LARGE_L - 1] = 0}};

    if (notZero != NOT_FOUND)
    {
        for (int i = 0; i < notZero; ++i)
        {
            cycleShiftLeft(num->mantissa.value, MANTISSA_L);
            sub_exp.value[EXPONENT_LARGE_L - 1]--;
        }
    }

    exponent_large_t new_exp;
    res = sub(exponent_large_t, num->exponent, sub_exp, &new_exp);
    copy(exponent_large_t, &new_exp, &num->exponent);

    return res;
}

typedef enum {
    START = 0,
    M_SIGN = 1,
    BEFORE_POINT = 2,
    POINT = 3,
    AFTER_POINT = 4,
    MNT_READY = 5,
    EXP_CHAR = 6,
    E_SIGN = 7,
    EXPONENT = 8,
    END = 9
} input_state;

err_t input_integer_num(FILE *f, real_input_t *num)
{
    input_state state = START;
    err_t res = OK;
    int mnt_index = 0;
    int exp_index = 0;
    int exp_add = 0;
    bool had_nz_bef_point = false;
    num->mantissa.sign = PLUS;
    num->exponent.sign = PLUS;
    while (state != END && res == OK)
    {
        int ch = getc(f);

        if (isspace(ch))
        {
            ch = EOF;
        }

        if (ch == EOF)
        {
            if (state == START)
            {
                res = EMPTY_INPUT;
            }
            else
            {
                state = END;
            }
        }
        else
        {
            if (state == START)
            {
                if (ch == '+')
                {
                    state = M_SIGN;
                    num->mantissa.sign = PLUS;
                }
                else if (ch == '-')
                {
                    state = M_SIGN;
                    num->mantissa.sign = MINUS;
                }
                else if (isdigit(ch))
                {
                    state = BEFORE_POINT;
                    int digit = to_int(ch);
                    if (digit != 0)
                    {
                        had_nz_bef_point = true;
                    }

                    if (had_nz_bef_point)
                    {
                        exp_add++;
                    }
                    num->mantissa.value[mnt_index++] = digit;
                }
                else
                {
                    res = WRONG_START;
                }
            }
            else if (state == M_SIGN)
            {
                if (isdigit(ch))
                {
                    state = BEFORE_POINT;
                    int digit = to_int(ch);
                    if (digit != 0)
                    {
                        had_nz_bef_point = true;
                    }

                    if (had_nz_bef_point)
                    {
                        exp_add++;
                    }
                    num->mantissa.value[mnt_index++] = digit;
                }
                else
                {
                    res = WRONG_INTEGER;
                }
            }
            else if (state == BEFORE_POINT)
            {
                if (mnt_index >= MANTISSA_L)
                {
                    res = OVERFLOW;
                }
                else if (isdigit(ch))
                {
                    int digit = to_int(ch);
                    if (digit != 0)
                    {
                        had_nz_bef_point = true;
                    }

                    if (had_nz_bef_point)
                    {
                        exp_add++;
                    }
                    num->mantissa.value[mnt_index++] = digit;
                }
                else
                {
                    res = WRONG_INTEGER;
                }
            }
            else
            {
                res = OTHER;
            }
        }
    }

    if (res == OK)
    {
        for (int i = 0; i < EXPONENT_LARGE_L - exp_index; i++)
        {
            cycleShiftRight(num->exponent.value, EXPONENT_LARGE_L);
        }

        res = normalize(num);

        if (res == OK)
        {
            exponent_large_t new_exp;

            //cppcheck-suppress legacyUninitvar
            exponent_large_t adding = {PLUS, {[0] = 0, [EXPONENT_LARGE_L - 1] = exp_add}};
            res = add(exponent_large_t, num->exponent, adding, &new_exp);
            copy(exponent_large_t, &new_exp, &num->exponent);
        }
    }

    return res;
}

err_t input_real_num(FILE *f, real_input_t *num)
{
    input_state state = START;
    err_t res = OK;
    int mnt_index = 0;
    int exp_index = 0;
    int exp_add = 0;
    bool had_nz_bef_point = false;
    num->mantissa.sign = PLUS;
    num->exponent.sign = PLUS;
    while (state != END && res == OK)
    {
        int ch = getc(f);

        if (isspace(ch))
        {
            if (ch == LF)
            {
                ch = EOF;
            }
            else if (state == BEFORE_POINT || state == AFTER_POINT )
            {
                state = MNT_READY;
                continue;
            }
            else if (state == EXP_CHAR)
            {
                continue;
            }
            else
            {
                ch = EOF;
            }
        }

        if (ch == EOF)
        {
            if (state == BEFORE_POINT || state == AFTER_POINT || state == MNT_READY || state == POINT || state == EXPONENT)
            {
                state = END;
            }
            else if (state == START)
            {
                res = EMPTY_INPUT;
            }
            else
            {
                res = END_TOO_SOON;
            }
        }
        else
        {
            if (state == START)
            {
                if (ch == '+')
                {
                    state = M_SIGN;
                    num->mantissa.sign = PLUS;
                }
                else if (ch == '-')
                {
                    state = M_SIGN;
                    num->mantissa.sign = MINUS;
                }
                else if (isdigit(ch))
                {
                    state = BEFORE_POINT;
                    int digit = to_int(ch);
                    if (digit != 0)
                    {
                        had_nz_bef_point = true;
                    }

                    if (had_nz_bef_point)
                    {
                        num->mantissa.value[mnt_index++] = digit;
                        exp_add++;
                    }
                }
                else if (ch == '.')
                {
                    state = POINT;
                }
                else
                {
                    res = WRONG_START;
                }
            }
            else if (state == M_SIGN)
            {
                if (isdigit(ch))
                {
                    state = BEFORE_POINT;
                    int digit = to_int(ch);
                    if (digit != 0)
                    {
                        had_nz_bef_point = true;
                    }

                    if (had_nz_bef_point)
                    {
                        num->mantissa.value[mnt_index++] = digit;
                        exp_add++;
                    }
                }
                else if (ch == '.')
                {
                    state = POINT;
                }
                else
                {
                    res = WRONG_AFTER_M_SIGN;
                }
            }
            else if (state == BEFORE_POINT)
            {
                if (mnt_index >= MANTISSA_L)
                {
                    res = OVERFLOW;
                }
                else if (isdigit(ch))
                {
                    int digit = to_int(ch);
                    if (digit != 0)
                    {
                        had_nz_bef_point = true;
                    }

                    if (had_nz_bef_point)
                    {
                        num->mantissa.value[mnt_index++] = digit;
                        exp_add++;
                    }
                }
                else if (ch == '.')
                {
                    state = POINT;
                }
                else if (ch == 'E')
                {
                    state = EXP_CHAR;
                }
                else
                {
                    res = WRONG_BEFORE_POINT;
                }
            }
            else if (state == POINT)
            {
                if (mnt_index >= MANTISSA_L)
                {
                    res = OVERFLOW;
                }
                else if (isdigit(ch))
                {
                    state = AFTER_POINT;
                    num->mantissa.value[mnt_index++] = to_int(ch);
                }
                else
                {
                    res = WRONG_AFTER_POINT;
                }
            }
            else if (state == AFTER_POINT)
            {
                if (mnt_index >= MANTISSA_L)
                {
                    res = OVERFLOW;
                }
                else if (isdigit(ch))
                {
                    num->mantissa.value[mnt_index++] = to_int(ch);
                }
                else if (ch == 'E')
                {
                    state = EXP_CHAR;
                }
                else
                {
                    res = WRONG_AFTER_POINT;
                }
            }
            else if (state == MNT_READY)
            {
                if (ch == 'E')
                {
                    state = EXP_CHAR;
                }
                else
                {
                    res = WRONG_AFTER_MNT_READY;
                }
            }
            else if (state == EXP_CHAR)
            {
                if (ch == '+')
                {
                    state = E_SIGN;
                    num->exponent.sign = PLUS;
                }
                else if (ch == '-')
                {
                    state = E_SIGN;
                    num->exponent.sign = MINUS;
                }
                else if (isdigit(ch))
                {
                    state = EXPONENT;
                    num->exponent.value[exp_index++] = to_int(ch);
                }
                else
                {
                    res = WRONG_AFTER_EXP_CHAR;
                }
            }
            else if (state == E_SIGN)
            {
                if (isdigit(ch))
                {
                    state = EXPONENT;
                    num->exponent.value[exp_index++] = to_int(ch);
                }
                else
                {
                    res = WRONG_AFTER_E_SIGN;
                }
            }
            else if (state == EXPONENT)
            {
                if (exp_index >= EXPONENT_L)
                {
                    res = OVERFLOW;
                }
                else if (isdigit(ch))
                {
                    num->exponent.value[exp_index++] = to_int(ch);
                }
                else
                {
                    res = WRONG_EXPONENT;
                }
            }
        }
    }

    if (res == OK)
    {
        for (int i = 0; i < EXPONENT_LARGE_L - exp_index; i++)
        {
            cycleShiftRight(num->exponent.value, EXPONENT_LARGE_L);
        }

        res = normalize(num);

        if (res == OK)
        {

            exponent_large_t new_exp;

            //cppcheck-suppress legacyUninitvar
            exponent_large_t adding = {PLUS, {[0] = 0, [EXPONENT_LARGE_L - 1] = exp_add}};
            res = add(exponent_large_t, num->exponent, adding, &new_exp);
            copy(exponent_large_t, &new_exp, &num->exponent);
        }
    }

    return res;
}

void input_to_inner(real_input_t *from, real_inner_t *to)
{
    copy_exponent_large_t(&from->exponent, &to->exponent, true);

    for (int i = 0; i < MANTISSA_L; i++)
    {
        to->mantissa.value[i] = from->mantissa.value[i];
    }

    to->mantissa.sign = from->mantissa.sign;
}

err_t divide_inner_t(real_inner_t *numerator, real_inner_t *denominator, real_inner_t *result)
{
    err_t rc = OK;
    if (abs_compare_mantissa_large_t(&denominator->mantissa, &ZERO_INNER.mantissa) == 0)
    {
        rc = ZERO_DIVISION;
    }
    else if (abs_compare_mantissa_large_t(&numerator->mantissa, &ZERO_INNER.mantissa) == 0)
    {
        *result = ZERO_INNER;
    }
    else {
        int cmp = abs_compare_mantissa_large_t(&numerator->mantissa, &denominator->mantissa);
        sign_t mant_sign = numerator->mantissa.sign * denominator->mantissa.sign;
        exponent_large_t diff = {PLUS, {[0] = 0}};

        sub_exponent_large_t(numerator->exponent, denominator->exponent, &diff);
        //cppcheck-suppress legacyUninitvar
        exponent_large_t one = {PLUS, {[EXPONENT_LARGE_L - 1] = 1}};

        if (cmp == 0)
        {
            *result = ONE_INNER;
            add_exponent_large_t(diff, one, &diff);
            result->exponent = diff;
            result->mantissa.sign = mant_sign;
        }
        else
        {
            real_inner_t temp_a = ZERO_NUMBER;
            real_inner_t temp_b = ZERO_NUMBER;
            real_inner_t temp = ZERO_NUMBER;
            copy_mantissa_large_t(&ZERO_INNER.mantissa, &result->mantissa, true);
            copy_exponent_large_t(&ZERO_INNER.exponent, &result->exponent, true);
            result->exponent = diff;

            result->mantissa.sign = mant_sign;

            copy_mantissa_large_t(&numerator->mantissa, &temp_a.mantissa, true);
            copy_exponent_large_t(&numerator->exponent, &temp_a.exponent, true);
            copy_mantissa_large_t(&denominator->mantissa, &temp_b.mantissa, true);
            copy_exponent_large_t(&numerator->exponent, &temp_b.exponent, true);
            temp_a.mantissa.sign = mant_sign;
            temp_b.mantissa.sign = mant_sign;

            int res_index = 0;

            while (abs_compare_mantissa_large_t(&temp_a.mantissa, &ZERO_INNER.mantissa) != 0 &&
                    abs_compare_mantissa_large_t(&temp_b.mantissa, &ZERO_INNER.mantissa) != 0)
            {
                while (abs_compare_mantissa_large_t(&temp_a.mantissa, &temp_b.mantissa) >= 0)
                {
                    // a = a - b;
                    abs_sub_mantissa_large_t(temp_a.mantissa, temp_b.mantissa, &temp.mantissa);
                    copy_mantissa_large_t(&temp.mantissa, &temp_a.mantissa, false);
                    // res = res + 1;
                    result->mantissa.value[res_index]++;
                }
                res_index++;
                shiftRight(temp_b.mantissa.value, MANTISSA_LARGE_L);
            }

            if (result->mantissa.value[0] == 0)
            {
                shiftLeft(result->mantissa.value, MANTISSA_LARGE_L);
            }
        }
    }

    return rc;
}

err_t inner_to_real(real_inner_t *inner, real_t *result)
{
    exponent_large_t maxExponent = {PLUS, {0, 9, 9, 9, 9, 9}};
    err_t rc = OK;
    if (abs_compare_exponent_large_t(&inner->exponent, &maxExponent) > 0)
    {
        rc = OVERFLOW_DIVISION;
    }
    else
    {
        real_t res = ZERO_NUMBER;
        exponent_t resExponent = { inner->exponent.sign, {inner->exponent.value[1], inner->exponent.value[2], inner->exponent.value[3], inner->exponent.value[4], inner->exponent.value[5]}};
        res.exponent = resExponent;
        res.mantissa.sign = inner->mantissa.sign;
        for (int i = 0; i < MANTISSA_L; ++i) {
            res.mantissa.value[i] = inner->mantissa.value[i];
        }

        if (inner->mantissa.value[MANTISSA_L] >= 5)
        {
            //cppcheck-suppress legacyUninitvar
            mantissa_t one = {PLUS, {[MANTISSA_L - 1] = 1}};
            abs_add_mantissa_t(res.mantissa, one, &res.mantissa);
        }

        *result = res;
    }

    return rc;
}

void print_err_t(err_t err)
{
    switch (err) {
        case OK:
            printf("Ok");
            break;
        case OVERFLOW:
            printf("overlow of format in input!");
            break;
        case EMPTY_INPUT:
            printf("empty input!");
            break;
        case END_TOO_SOON:
            printf("parsing ended too soon!");
            break;
        case WRONG_START:
            printf("parsing error!");
            break;
        case WRONG_AFTER_M_SIGN:
        case WRONG_BEFORE_POINT:
            printf("wrong symbol before decimal point");
            break;
        case WRONG_AFTER_POINT:
            printf("wrong symbol after decimal point");
            break;
        case WRONG_AFTER_MNT_READY:
            printf("wrong symbol after mantissa!");
            break;
        case WRONG_AFTER_EXP_CHAR:
        case WRONG_AFTER_E_SIGN:
        case WRONG_EXPONENT:
            printf("exponent parse error!");
            break;
        case ZERO_DIVISION:
            printf("zero divizion!");
            break;
        case OVERFLOW_DIVISION:
            printf("division leads to overflow!");
            break;
        case WRONG_INTEGER:
            printf("integer number parsing error");
            break;
        default:
            printf("unknown error");
            break;
    }
}