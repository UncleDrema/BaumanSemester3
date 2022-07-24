//
// Created by archdrema on 7/24/22.
//

#include "sign.h"

void print_sign(FILE *f, sign_t sign)
{
    switch (sign) {
        case PLUS:
            putc('+', f);
            break;
        case MINUS:
            putc('-', f);
            break;
        default:
            putc('?', f);
            break;
    }
}