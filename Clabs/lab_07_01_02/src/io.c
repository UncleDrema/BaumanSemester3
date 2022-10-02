// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/25/22.
// Реализация функций файлового ввода-вывода

#include <io.h>
#include <safe_free.h>
#include <stdlib.h>

err_t read_int_array(FILE *f, int **pb, int **pe)
{
    if (f == NULL)
    {
        return ERR_IO;
    }

    int num;
    int rc;
    size_t count = 0;

    while ((rc = fscanf(f, "%d", &num)) == 1)
    {
        count++;
    }

    if (rc == 0 || (rc == EOF && ferror(f)))
    {
        return ERR_IO;
    }

    if (fseek(f, 0, SEEK_SET) != OK)
    {
        return ERR_IO;
    }

    *pb = malloc(count * sizeof(int));
    *pe = *pb + count;

    int *p;

    for (p = *pb; p < *pe && fscanf(f, "%d", &num) == 1; *p = num, p++);

    if (p != *pe || ferror(f))
    {
        SAFE_FREE(*pb);
        return ERR_IO;
    }

    return OK;
}

void write_int_array(FILE *f, const int *pb, const int *pe)
{
    while (pb < pe)
    {
        fprintf(f, "%d ", *pb++);
    }
}