//
// Created by archdrema on 12/8/22.
//

#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include <stddef.h>

typedef struct hashtable_t hashtable_t;

typedef struct entry_t entry_t;

/// Создать хеш-таблицу на основе строки
hashtable_t *create_table(char *str);

/// Освободить хеш-таблицу
void free_table(hashtable_t *table);

/// Поместить символ в хеш-таблицу
void hashtable_put(hashtable_t *table, char ch);

/// Поиск в записи по символу в хеш-таблице
entry_t *hashtable_find(hashtable_t *table, char ch);

/// Поиск в записи по символу в хеш-таблице с возвратом числа сравнений
entry_t *hashtable_find_get_compares(hashtable_t *table, char ch, size_t *cmp_count);

/// Удаление записи по символу из хеш-таблицы
void hashtable_remove(hashtable_t *table, char ch);

/// Получить символ из записи
char get_entry_char(const entry_t *entry);

/// Получить число вхождений из записи
size_t get_entry_count(const entry_t *entry);

/// Получить количество элементов в хеш-таблице
size_t get_len(hashtable_t *table);

/// Вывести хеш-таблицу
void print_table(hashtable_t *table);

/// Получить среднее число сравнений при поиске элементов
float hashtable_avg_cmp(hashtable_t *table);

/// Получить размер хеш-таблицы в байтах
size_t hashtable_sizeof(hashtable_t *table);

/// Удалить повторяющиеся
void hashtable_remove_repeating(hashtable_t *table);

#endif
