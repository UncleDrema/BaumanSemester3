//
// Created by archdrema on 9/25/22.
// Заголовочный файл функций ввода-вывода

#ifndef __IO_H
#define __IO_H
#include <stdio.h>
#include <err.h>

/**
 * Считывает массив целых чисел из потока
 * @param f поток ввода
 * @param pb указатель на начало массива
 * @param pe указатель на конец массива
 * @attention в функции выделяется динамическая память и присваивается @b pb, требуется освобождение, если не возвращена ошибка!
 */
err_t read_int_array(FILE *f, int **pb, int **pe);

/**
 * Записать массив целых чисел в поток
 * @param f поток вывода
 * @param pb указатель на начало массива
 * @param pe указатель на конец массива
 */
void write_int_array(FILE *f, const int *pb, const int *pe);

#endif
