#include "stat.h"
#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_WRONG_ARGS 1
#define ERR_FILE 2
#define ERR_DATA 3
#define IS_THREEE_SIGMA(val) (val >= 0.9973)

int count_three_sigma_percent(FILE *f, float *percent);

int check_in_segment(float val, float point, float delta);

int main(int argc, char *argv[])
{
    int return_code = OK;

    if (argc != 2)
        return_code = ERR_WRONG_ARGS;
    else
    {
        FILE *f = fopen(argv[1], "r");

        if (f == NULL)
        {
            return_code = ERR_FILE;
        }
        else
        {
            float res;
            return_code = count_three_sigma_percent(f, &res);

            if (return_code == OK)
            {
                puts(IS_THREEE_SIGMA(res) ? "1" : "0");
            }

            fclose(f);
        }
    }

    return return_code;
}

int count_three_sigma_percent(FILE *f, float *percent)
{
    float disp, av;

    return (rewind(f), count_average(f, &av)) == OK && (rewind(f), count_disp(f, av, &disp)) == OK && (rewind(f), count_good_percent(f, check_in_segment, av, 3 * sqrtf(disp), percent)) == OK ? OK : ERR_DATA;
}

int check_in_segment(float val, float point, float delta)
{
    return fabs(point - val) < delta;
}
