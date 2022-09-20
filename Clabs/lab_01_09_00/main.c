#include <stdio.h>
#include <math.h>
#define OK 0
#define ERR_IO 1
#define SUCCESS 2
#define EMPTY 3
#define EPS 0.0000001

int task(float*);

int main()
{
    int return_code;
    float res = 0;

    switch (task(&res))
    {
        case ERR_IO:
            printf("Error: invalid input\n");
            return_code = 1;
            break;
        case EMPTY:
            printf("Error: sequence is empty\n");
            return_code = 1;
            break;
        case SUCCESS:
            printf("Result: %f\n", res);
            return_code = 0;
            break;
    }
    return return_code;
}

int task(float*result)
{
    float x;
    int state = OK, i;
    for (i = 1; state == OK; i++)
    {
        printf("Please input element: ");
        if (!scanf("%f", &x))
        {
            state = ERR_IO;
        }
        else if (x < 0)
        {
            state = SUCCESS;
        }
        else
        {
            *result += x / i;
        }
    }

    if (state == SUCCESS)
    {
        if (i < 3)
        {
            state = EMPTY;
        }
        else
        {
            *result = sqrtf(*result);
        }
    }

    return state;
}
