//
// Created by archdrema on 11/17/22.
//

#ifndef __TIME_UTILS_H
#define __TIME_UTILS_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

double rand_range(double min, double max);

void sleep_seconds(float seconds);

double abs_err(double expected, double measured);

int skip_to_nl(FILE *f);

#endif
