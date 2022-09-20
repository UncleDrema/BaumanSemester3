#ifndef __STUDENT_H
#define __STUDENT_H

#include <stdint.h>
#include <stdio.h>
#include <printf.h>
#include <stdarg.h>

#define SURNAME_LEN 26
#define NAME_LEN 11
#define MARKS_AMOUNT 4

#define EMPTY_STUDENT {"", "", {0, 0, 0, 0}}

typedef struct student
{
    char surname[SURNAME_LEN];
    char name[NAME_LEN];
    uint32_t marks[MARKS_AMOUNT];
} student;

int scan_student(FILE *stream, student *st);

void print_student(FILE *stream, student *st);

float av_mark(student *st);

int compare_students(student *first, student *second);

#endif
