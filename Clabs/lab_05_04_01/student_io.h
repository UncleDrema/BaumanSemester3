#ifndef __STUDENT_IO_H
#define __STUDENT_IO_H
#include <stdio.h>
#include "student.h"

void get_student_by_pos(FILE *f, int index, student *st);

void put_student_by_pos(FILE *f, int index, student *st);

int get_student_count(FILE *f);

#endif
