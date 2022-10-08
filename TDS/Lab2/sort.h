//
// Created by archdrema on 9/20/22.
// Заголовочный файл функций сортировки и вспомогательных для неё функций

#ifndef __SORT_H
#define __SORT_H

#include <stddef.h>
#include "err.h"

/**
 * Переместить элемент массива на заданную позицию левее исходной
 * @param arr обрабатываемый массив
 * @param from позиция элемента массива
 * @param to новая позиция
 * @param len длина массива
 * @param size размер одного элемента массива
 * @return код ошибки
 */
err_t move_to_pos(void *arr, void *from, void *to, size_t len, size_t size);

/**
 * Универсальная сортировка (в реализации - сортирвока вставками с двоичным поиском)
 * @param first указатель на начало сортируемого массива
 * @param number размер массива
 * @param size размер одного элемента массива
 * @param comparator компаратор для сравнения элементов массива
 * @warning при получении некорректных параметров, ничего не делает
 */
void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));

/**
 * Возвращает указатель на элемент массива по индексу
 * @param arr массив
 * @param index индекс элемента
 * @param size размер элемента массива
 * @return указатель на элемент массива
 * @warning требуется передавать индекс, не выходящий за пределы массива!
 * @warning в случае, если size равен нулю, возвращает указатель на первый элемент массива
 */
void *at_index(void *arr, size_t index, size_t size);

#endif
