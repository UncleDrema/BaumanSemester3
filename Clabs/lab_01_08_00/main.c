#include <stdio.h>
#include <limits.h>
#define ERR_IO 1
#define ERR_INVALID 2
#define BIG_BIT 2147483648
#define SMALL_BIT 1

unsigned int cycle_shift_right(unsigned int);
unsigned int cycle_sh_r_n(unsigned int, int);
void uint_to_binary(unsigned int, char*);

int main()
{
    int return_code, n;
    unsigned int a;

    printf("Input A and N: ");
    if (scanf("%u%i", &a, &n) != 2)
    {
        printf("Error: Please input unisgned value and int value\n");
        return_code = ERR_IO;
    }
    else if (n < 0)
    {
        printf("Error: N must be more than -1!\n");
        return_code = ERR_INVALID;
    }
    else
    {
        a = cycle_sh_r_n(a, n % 32);

        char bin[32];
        uint_to_binary(a, bin);
        printf("Result: %s\n", bin);

        return_code = 0;
    }

    return return_code;
}

unsigned int cycle_sh_r_n(unsigned int a, int n)
{
    for (int i = 0; i < n; i++)
    {
        a = cycle_shift_right(a);
    }

    return a;
}

unsigned int cycle_shift_right(unsigned int a)
{
    unsigned int addition = a % 2 ? BIG_BIT : 0;
    a >>= 1;
    a += addition;
    return a;
}

void uint_to_binary(unsigned int a, char*c)
{
    c[32] = '\0';
    int count = 0;
    for (unsigned int i = BIG_BIT; i > 0; i >>= 1)
    {
        c[count] = a & i ? '1' : '0';
        count++;
    }
}
