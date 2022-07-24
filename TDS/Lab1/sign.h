//
// Created by archdrema on 7/24/22.
//

#include "stdio.h"

#ifndef LAB1_SIGN_H
#define LAB1_SIGN_H

typedef enum sign { PLUS = 1, MINUS = -1 } sign_t;

void print_sign(FILE *f, sign_t sign);

#endif //LAB1_SIGN_H
