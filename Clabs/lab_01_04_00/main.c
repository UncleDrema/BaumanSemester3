#include <stdio.h>

int count_bottles(int, int, int);

int main()
{
    printf("Input amount of money: ");
    int money;
    int full_cost = 45, empty_cost = 20;
    scanf("%i", &money);

    int bottles = count_bottles(money, full_cost, empty_cost);

    printf("Bottles you can buy: %i\n", bottles);
    return 0;
}

int count_bottles(int money, int f_cost, int e_cost)
{
    return (money - e_cost) / (f_cost - e_cost);
}
