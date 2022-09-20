#ifndef __CONVERTIO_H
#define __CONVERTIO_H

#include <stdio.h>

#define OK 0
#define ERR_READ -1

#define GEN_IO_HEADER(TYPE) \
int convert_##TYPE##_t2b(FILE *in, FILE *out);\
int convert_##TYPE##_b2t(FILE *in, FILE *out, char *delimeter, char *end);

#define GEN_IO_BODY(TYPE, SCAN_FMT, PRINT_FMT) \
int convert_##TYPE##_t2b(FILE *in, FILE *out)\
{\
    TYPE cur;\
    int scan_code;\
    while ((scan_code = fscanf(in, SCAN_FMT, &cur)) == 1)\
    {\
        fwrite(&cur, sizeof(TYPE), 1, out);\
    }\
    return scan_code == -1 ? 0 : -1;\
}\
int convert_##TYPE##_b2t(FILE *in, FILE *out, char *delimeter, char *end)\
{\
    TYPE cur;\
    if (fread(&cur, sizeof(TYPE), 1, in) == 1)\
    {\
        fprintf(out, PRINT_FMT, cur);\
        while (fread(&cur, sizeof(TYPE), 1, in) == 1)\
        {\
            fprintf(out, "%s", delimeter);\
            fprintf(out, PRINT_FMT, cur);\
        }\
        fprintf(out, "%s", end);\
    }\
    char c;\
    return fread(&c, sizeof(char), 1, in) == 0 ? 0 : -1;\
}

#define CONVERT_T2B(TYPE, in, out) convert_##TYPE##_t2b(in, out)
#define CONVERT_B2T(TYPE, in, out, delimeter, end) convert_##TYPE##_b2t(in, out, delimeter, end)

#endif
