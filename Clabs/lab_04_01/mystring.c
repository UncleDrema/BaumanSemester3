#include <stddef.h>
#include "mystring.h"

#define OK 0
#define STOP 1

const char *my_strpbrk(const char *s, const char *accept)
{
    const char *res = NULL;
    const char *accept_start = accept;

    while (*s && !res)
    {
        while (*accept && !res)
        {
            res = *s == *accept++ ? s : NULL;
        }
        accept = accept_start;
        s++;
    }

    return res;
}

size_t my_strspn(const char *str, const char *accept)
{
    size_t count = 0;
    int state = OK;
    const char *accept_start = accept;
    while (*str && state == OK)
    {
        state = STOP;
        while (*accept && state == STOP)
        {
            if (*str == *accept)
                state = OK;
            accept++;
        }

        accept = accept_start;

        if (state == OK)
            count++;

        str++;
    }

    return count;
}

size_t my_strcspn(const char *str, const char *reject)
{
    size_t count = 0;
    int state = OK;
    const char *reject_start = reject;
    while (*str && state == OK)
    {
        state = OK;
        while (*reject && state == OK)
        {
            if (*str == *reject)
                state = STOP;
            reject++;
        }

        reject = reject_start;

        if (state == OK)
            count++;

        str++;
    }

    return count;
}

const char *my_strchr(const char *s, int c_in)
{
    while (*s && *s != c_in)
        s++;
    return *s == c_in ? s : NULL;
}

const char *my_strrchr(const char *s, int c)
{
    const char *last;
    for (last = NULL; *s; s++)
        last = *s == c ? s : last;
    return *s == c ? s : last;
}
