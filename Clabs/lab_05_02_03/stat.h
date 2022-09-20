#ifndef __STAT_H
#define __STAT_H

#include <stdio.h>

#define OK 0
#define ERR_NOT_ENOUGH_DATA -1

int count_average(FILE *f, float *av);

int count_disp(FILE *f, float av, float *disp);

int count_good_percent(FILE *f, int (*filter)(float, float, float), float param1, float param2, float *percent);

#endif
