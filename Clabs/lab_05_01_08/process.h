#ifndef __PROCESS_H
#define __PROCESS_H

#include <stdio.h>

#define OK 0
#define NOT_FOUND -1
#define ERR_NOT_ENOUGH_DATA -1
#define ERR_NOT_ENOUGH_LOC_MAX -2

int process(FILE *f, int *min_loc_max_dist);

#endif
