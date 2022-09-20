#include <stdio.h>
#include <math.h>
#define ERR_IO 1
#define ERR_INVALID 2

float f(float);

float approx(float, float);

float abs_diff(float, float);

float rel_diff(float, float);

float nth_coeff(int);

int main()
{
    float x, eps;
    int return_code;

    printf("Input X and Eps: ");
    if (scanf("%f%f", &x, &eps) != 2)
    {
        printf("Input error! Please input real numbers\n");
        return_code = ERR_IO;
    }
    else
    {
        if (x > 1 || x < -1)
        {
            printf("X must be in [-1;1]!\n");
            return_code = ERR_INVALID;
        }
        else if (eps <= 0 || eps > 1)
        {
            printf("Eps must be in (0, 1]!\n");
            return_code = ERR_INVALID;
        }
        else
        {
            float approx_val, real_val, absolute, relative;

            real_val = f(x);
            approx_val = approx(x, eps);
            absolute = abs_diff(real_val, approx_val);
            relative = rel_diff(absolute, real_val);

            printf("s(x): %f\nf(x): %f\nabsDelta: %f\nrelDelta: %f\n", approx_val, real_val, absolute, relative);
            return_code = 0;
        }
    }

    return return_code;
}

float f(float x)
{
    return asinf(x);
}

float approx(float x, float eps)
{
    float elem = x, sum = elem;

    for (int n = 1; fabsf(elem) >= eps; n++)
    {
        elem = powf(x, 2 * n + 1) * nth_coeff(n);
        sum += elem;
    }

    return sum;
}

float abs_diff(float real, float approx)
{
    return fabsf(real - approx);
}

float rel_diff(float abs, float real)
{
    return abs / fabsf(real);
}

float nth_coeff(int n)
{
    float res = 1;
    for (int i = 1; i <= 2 * n; i++)
    {
        if (i <= n)
        {
            res /= i;
            res /= 4;
        }
        else
        {
            res *= i;
        }
    }
    res /= (2 * n + 1);
    return res;
}
