#include "string_utils.h"

int starts_with(char *str, char *prefix)
{
    int return_code = YES;
    while (*prefix && *str)
    {
        if (*prefix++ != *str++)
        {
            return_code = NO;
            break;
        }
    }

    if (!*str && *prefix)
        return_code = ERR_PREFIX_TOO_BIG;

    return return_code;
}
