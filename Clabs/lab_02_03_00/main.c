#include <stdio.h>
#define ERR_IO 1
#define ERR_INVALID 2
#define OK 0
#define ERR_ALL_DELETED 3
#define INP_ERR -1
#define N 10

int input_array(int *arr, int n);
void print_array(int *arr, int n);
int is_palindrome(int num);
int delete_palindroms(int *arr, int n);

int main(void)
{
    int return_code = 0, arr[N], n;

    printf("%s", "Please, input n: ");
    if (scanf("%d", &n) != 1)
    {
        printf("%s", "Error, n must be an integer!\n");
        return_code = ERR_IO;
    }
    else if (n < 1 || n > N)
    {
        printf("%s", "Error, n must be from one to ten!\n");
        return_code = ERR_INVALID;
    }
    else if (input_array(arr, n) != OK)
    {
        printf("%s", "Error, element must be an integer!\n");
        return_code = ERR_INVALID;
    }
    else
    {
        int new_n = delete_palindroms(arr, n);
        if (new_n == 0)
        {
            return_code = ERR_ALL_DELETED;
        }
        else
        {
            print_array(arr, new_n);
        }
    }

    return return_code;
}

int is_palindrome(int num)
{
    int return_code = 0;
    if (num >= 0)
    {
        int rev = 0, prev = num;
        while (num > 0)
        {
            rev = rev * 10 + (num % 10);
            num /= 10;
        }

        return_code = prev == rev;
    }

    return return_code;
}

int delete_palindroms(int *arr, int n)
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        arr[j] = arr[i];
        if (!is_palindrome(arr[i]))
        {
            j++;
        }
    }

    return j;
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

int input_array(int *arr, int n)
{
    int return_code = OK;
    printf("%s", "Please, input array elements: ");
    for (int i = 0; i < n && (return_code = ((scanf("%d", arr + i) == 1) ? OK : INP_ERR)) == OK; i++);
    return return_code;
}
