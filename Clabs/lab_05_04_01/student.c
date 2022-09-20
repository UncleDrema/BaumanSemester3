#include "student.h"
#include <stdlib.h>
#include <string.h>

void print_student(FILE *stream, student *st)
{
    fprintf(stream, "%s %s %u %u %u %u", st->surname, st->name, st->marks[0], st->marks[1], st->marks[2], st->marks[3]);
}

int scan_student(FILE *stream, student *st)
{
    return fscanf(stream, "%s %s %u %u %u %u", st->surname, st->name, st->marks, st->marks + 1, st->marks + 2, st->marks + 3);
}

float av_mark(student *st)
{
    float av = 0;
    for (int i = 0; i < MARKS_AMOUNT; i++)
        av += st->marks[i];
    return av / MARKS_AMOUNT;
}

int compare_students(student *first, student *second)
{
    int result = strcmp(first->surname, second->surname);
    if (!result)
        result = strcmp(first->name, second->name);
    return result;
}
