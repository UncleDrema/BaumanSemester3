#ifndef __CONVERTIO_H
#define __CONVERTIO_H

#include <stdio.h>

#define OK 0
#define ERR_READ -1

#define GEN_IO_HEADER(TYPE) \
int convert_##TYPE##_t2b(FILE *in, FILE *out);\
int convert_##TYPE##_b2t(FILE *in, FILE *out, char *delimeter, char *end);

#define GEN_CUSTOM_IO_HEADER(TYPE) \
int custom_convert_##TYPE##_t2b(FILE *in, FILE *out, int (*custom_scan) (FILE*, TYPE*));\
int custom_convert_##TYPE##_b2t(FILE *in, FILE *out, void (*custom_print) (FILE*, TYPE*), char *delimeter, char *end);

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

#define GEN_CUSTOM_IO_BODY(TYPE, DEFAULT) \
int custom_convert_##TYPE##_t2b(FILE *in, FILE *out, int (*custom_scan) (FILE*, TYPE*))\
{\
    TYPE cur = DEFAULT;\
    int scan_code;\
    while ((scan_code = custom_scan(in, &cur)) > 0)\
    {\
        fwrite(&cur, sizeof(TYPE), 1, out);\
    }\
    return scan_code == -1 ? 0 : -1;\
}\
int custom_convert_##TYPE##_b2t(FILE *in, FILE *out, void (*custom_print) (FILE*, TYPE*), char *delimeter, char *end)\
{\
    TYPE cur = DEFAULT;\
    if (fread(&cur, sizeof(TYPE), 1, in) == 1)\
    {\
        custom_print(out, &cur);\
        while (fread(&cur, sizeof(TYPE), 1, in) > 0)\
        {\
            fprintf(out, "%s", delimeter);\
            custom_print(out, &cur);\
        }\
        fprintf(out, "%s", end);\
    }\
    char c;\
    return fread(&c, sizeof(char), 1, in) == 0 ? 0 : -1;\
}

#define CONVERT_T2B(TYPE, in, out) convert_##TYPE##_t2b(in, out)
#define CONVERT_B2T(TYPE, in, out, delimeter, end) convert_##TYPE##_b2t(in, out, delimeter, end)

#define CUSTOM_CONVERT_T2B(TYPE, in, out, custom_scan) custom_convert_##TYPE##_t2b(in, out, custom_scan)
#define CUSTOM_CONVERT_B2T(TYPE, in, out, custom_print, delimeter, end) custom_convert_##TYPE##_b2t(in, out, custom_print, delimeter, end)

#endif
