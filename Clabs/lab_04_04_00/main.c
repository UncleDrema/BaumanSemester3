#include <stdio.h>
#include <string.h>
#include "ip_parsing.h"

#define BUF_SIZE 258
#define ERR_EOF 1
#define ERR_BUF 2
#define OK 0

int main(void)
{
    int return_code = OK;
    char string[BUF_SIZE];

    string[BUF_SIZE - 2] = '\0';

    fgets(string, BUF_SIZE, stdin);

    if (feof(stdin))
    {
        return_code = ERR_EOF;
    }
    else if (string[BUF_SIZE - 2] != '\0' && string[BUF_SIZE - 2] != '\n')
    {
        return_code = ERR_BUF;
    }
    else
    {
        puts(is_valid_ip(string) ? "YES" : "NO");
    }

    return return_code;
}

