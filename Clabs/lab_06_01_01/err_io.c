//
// Created by archdrema on 9/11/22.
//

#include "err_io.h"

FUNC(FILE*, err_fopen, const char *restrict file_name, const char *restrict mode)
{
    FILE* res = fopen(file_name, mode);

    if (res == NULL)
    {
        THROW(OPEN_ERR, NULL);
    }
    return res;
}

FUNC(void, err_fclose, FILE *filestream)
{
    if (fclose(filestream) == EOF)
    {
        THROWN(CLOSE_ERR);
    }
}