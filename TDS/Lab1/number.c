//
// Created by archdrema on 7/24/22.
//

#include <ctype.h>
#include "number.h"
#include "utils.h"

impl_long_num(MANTISSA_L, mantissa_t)

impl_long_num(EXPONENT_L, exponent_t)

void print_real(FILE *f, real_t *num)
{
    print_sign(f, num->mantissa.sign);
    fprintf(f, " 0.");

    for (int i = 0; i <= firstNotEqualFromEnd(num->mantissa.value, MANTISSA_L, 0); i++)
    {
        putc(to_char(num->mantissa.value[i]), f);
    }

    fprintf(f, " E ");
    print_sign(f, num->exponent.sign);
    putc(' ', f);

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

static err_t normalize(real_t *num)
{
    err_t res;
    int notZero = firstNotEqual(num->mantissa.value, MANTISSA_L, 0);
    exponent_t sub_exp = {MINUS, {[EXPONENT_L - 1] = 0}};

    if (notZero != NOT_FOUND)
    {
        for (int i = 0; i < notZero; ++i)
        {
            cycleShiftLeft(num->mantissa.value, MANTISSA_L);
            sub_exp.value[EXPONENT_L - 1]++;
        }
    }

    exponent_t new_exp;
    res = sub(exponent_t, num->exponent, sub_exp, &new_exp);
    copy(exponent_t, &new_exp, &num->exponent);

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

err_t input_num(FILE *f, real_t *num)
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
        int ch  = getc(f);
        if (isspace(ch))
        {
            if (state == BEFORE_POINT || state == AFTER_POINT )
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
                        exp_add++;
                    }
                    num->mantissa.value[mnt_index++] = digit;
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
                        exp_add++;
                    }
                    num->mantissa.value[mnt_index++] = digit;
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
                        exp_add++;
                    }
                    num->mantissa.value[mnt_index++] = digit;
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
        for (int i = 0; i < EXPONENT_L - exp_index; i++)
        {
            cycleShiftRight(num->exponent.value, EXPONENT_L);
        }

        res = normalize(num);

        if (res == OK)
        {

            exponent_t new_exp;

            exponent_t adding = {PLUS, {[EXPONENT_L - 1] = exp_add}};
            res = add(exponent_t, num->exponent, adding, &new_exp);
            copy(exponent_t, &new_exp, &num->exponent);
        }
    }

    return res;
}