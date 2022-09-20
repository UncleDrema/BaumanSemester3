#include "string_parsing.h"
#include <ctype.h>
#include <stddef.h>

char *skip_blank(char *str)
{
    while (*str && isspace(*str))
        str++;
    return str;
}

char *skip_char(char *str, char c)
{
    return *str == c ? ++str : NULL;
}

int to_digit(char c)
{
    int temp = c;
    return isdigit(temp) ? temp - '0' : NOT_DIGIT;
}

char *skip_digits(char *str)
{
    while (*str && to_digit(*str) != NOT_DIGIT)
        str++;
    return str;
}
