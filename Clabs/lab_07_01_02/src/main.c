// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/12/22.
//
// Сортировка 4, фильтр 2
#include <sort.h>
#include <io.h>
#include <filter.h>
#include <comparators.h>
#include <safe_free.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    err_t rc = OK;
    bool filter = false;

    if (argc < 3)
    {
        rc = ERR_NOT_ENOUGH_ARGS;
    }
    else if (argc == 3 || (argc == 4 && (strcmp(argv[3], "f") == 0)))
    {
        if (argc == 4)
        {
            filter = true;
        }

        FILE *in, *out;

        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");

        if (in != NULL && out != NULL)
        {
            int *pb = NULL, *pe = NULL;
            int *pb_f = NULL, *pe_f = NULL;
            int **cur_pb = &pb, **cur_pe = &pe;

            rc = read_int_array(in, &pb, &pe);

            if (rc == OK && (pb == pe))
            {
                rc = ERR_DATA;
            }

            if (rc == OK)
            {
                if (filter)
                {
                    rc = key(pb, pe, &pb_f, &pe_f);
                    cur_pb = &pb_f;
                    cur_pe = &pe_f;
                }

                if (rc == OK)
                {
                    mysort(*cur_pb, *cur_pe - *cur_pb, sizeof(int), int_comparator);

                    write_int_array(out, *cur_pb, *cur_pe);
                }
            }

            SAFE_FREE(pb);
            SAFE_FREE(pb_f);
        }
        else
        {
            rc = ERR_IO;
        }

        if (in != NULL)
        {
            fclose(in);
        }
        if (out != NULL)
        {
            fclose(out);
        }
    }
    else
    {
        rc = ERR_WRONG_ARGS;
    }

    return rc;
}