#include "process.h"

int process(FILE *f, int *min_loc_max_dist)
{
    int return_code = OK;
    int prev, cur, temp;
    int prev_max_ind = NOT_FOUND, cur_max_ind = NOT_FOUND;
    int cur_index = 1;
    if (fscanf(f, "%d", &prev) != 1 || fscanf(f, "%d", &cur) != 1)
    {
        return_code = ERR_NOT_ENOUGH_DATA;
    }
    else
    {
        while (fscanf(f, "%d", &temp) == 1)
        {
            cur_index++;
            if (cur > temp && cur > prev)
            {
                if (prev_max_ind == NOT_FOUND)
                {
                    prev_max_ind = cur_index;
                }
                else if (cur_max_ind == NOT_FOUND)
                {
                    cur_max_ind = cur_index;
                    *min_loc_max_dist = cur_max_ind - prev_max_ind;
                }
                else
                {
                    prev_max_ind = cur_max_ind;
                    cur_max_ind = cur_index;
                    if (cur_max_ind - prev_max_ind < *min_loc_max_dist)
                    {
                        *min_loc_max_dist = cur_max_ind - prev_max_ind;
                    }
                }
            }

            prev = cur;
            cur = temp;
        }
    }

    if (cur_max_ind == NOT_FOUND)
        return_code = ERR_NOT_ENOUGH_LOC_MAX;

    return return_code;
}
