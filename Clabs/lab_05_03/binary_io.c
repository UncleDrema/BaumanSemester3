#include "binary_io.h"

int get_number_by_pos(FILE *f, int index)
{
    fseek(f, sizeof(int) * index, SEEK_SET);
    int result;
    fread(&result, sizeof(int), 1, f);
    return result;
}

void put_number_by_pos(FILE *f, int index, int number)
{
    fseek(f, sizeof(int) * index, SEEK_SET);
    fwrite(&number, sizeof(int), 1, f);
}

int get_number_count(FILE *f)
{
    int num, count = 0;
    fread(&num, sizeof(int), 1, f);
    while (!feof(f))
    {
        count++;
        fread(&num, sizeof(int), 1, f);
    }
    return count;
}
