#include "stat.h"

int count_average(FILE *f, float *av)
{
    int return_code = OK;
    int n = 0;
    float val, sum = 0;
    while (fscanf(f, "%f", &val) == 1)
    {
        sum += val;
        n++;
    }

    if (n == 0)
        return_code = ERR_NOT_ENOUGH_DATA;
    else
        *av = sum / n;
    return return_code;
}

int count_disp(FILE *f, float av, float *disp)
{
    int return_code = OK;
    int n = 0;
    float val, sq_err_sum = 0;
    while (fscanf(f, "%f", &val) == 1)
    {
        val = val - av;
        sq_err_sum += val * val;
        n++;
    }

    if (n <= 1)
        return_code = ERR_NOT_ENOUGH_DATA;
    else
        *disp = sq_err_sum / (n - 1);

    return return_code;
}

int count_good_percent(FILE *f, int (*filter)(float seq_el, float param1, float param2), float param1, float param2, float *percent)
{
    int total_size = 0, good_size = 0, return_code = OK;
    float val;

    while (fscanf(f, "%f", &val) == 1)
    {
        total_size++;
        if (filter(val, param1, param2))
        {
            good_size++;
        }
    }

    if (total_size > 0)
        *percent = ((float) good_size) / total_size;
    else
        return_code = ERR_NOT_ENOUGH_DATA;

    return return_code;
}
