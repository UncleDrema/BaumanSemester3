#include "student_io.h"
#include <stdio.h>

void get_student_by_pos(FILE *f, int index, student *st)
{
    fseek(f, sizeof(student) * index, SEEK_SET);
    fread(st, sizeof(student), 1, f);
}

void put_student_by_pos(FILE *f, int index, student *st)
{
    fseek(f, sizeof(student) * index, SEEK_SET);
    fwrite(st, sizeof(student), 1, f);
}

int get_student_count(FILE *f)
{
    student st;
    int count = 0;
    fread(&st, sizeof(student), 1, f);
    while (!feof(f))
    {
        count++;
        fread(&st, sizeof(student), 1, f);
    }
    return count;
}
