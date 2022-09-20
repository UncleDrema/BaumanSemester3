#include <stdio.h>
#define ERR_EMPTY 2
#define END_OF_INPUT 1
#define FULL 100
#define OK 0
#define N 10

int input_array(int *arr, int *count);
int find_min_index(int *arr, int n);
void swap(int *a, int *b);
void select_sort(int *arr, int n);
void print_array(int *arr, int n);

int main(void)
{
    int return_code = OK, arr[N], n;

    printf("%s", "Input array: ");
    switch (input_array(arr, &n))
    {
        case ERR_EMPTY:
            printf("%s", "Error, array can not be empty!\n");
            return_code = 1;
            break;
        case FULL:
            return_code = FULL;
            select_sort(arr, n);
            print_array(arr, n);
            break;
        case END_OF_INPUT:
            select_sort(arr, n);
            print_array(arr, n);
            break;
    }

    return return_code;
}

int find_min_index(int *arr, int n)
{
    int min_ind = 0;
    int min_el = arr[min_ind];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min_el)
        {
            min_el = arr[i];
            min_ind = i;
        }
    }

    return min_ind;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void select_sort(int *arr, int n)
{
    int head = 0, min;

    while (head < n)
    {
        min = find_min_index(arr + head, n - head) + head;
        swap(arr + head, arr + min);
        head++;
    }
}

void print_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i != n - 1)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }
}

int input_array(int *arr, int *count)
{
    int i = 0, state = OK, temp;
    while (state == OK)
    {
        if (scanf("%d", &temp) != 1)
        {
            state = END_OF_INPUT;
        }
        else
        {

            if (i < N)
            {
                arr[i] = temp;
                i++;
            }
            else
            {
                state = FULL;
            }
        }
    }

    *count = i;
    if (i == 0)
    {
        state = ERR_EMPTY;
    }

    return state;
}
