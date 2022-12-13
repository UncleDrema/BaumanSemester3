//
// Created by archdrema on 12/8/22.
//

#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>

#define INIT_CAPACITY 3

#define REHASH_FACTOR 5

#define PRIME_CONST 97

struct hashtable_t
{
    size_t capacity;
    size_t len;
    entry_t **arr;
};

struct entry_t
{
    char ch;
    size_t count;
    entry_t *next;
};

static entry_t *alloc_entry(char ch, size_t count)
{
    entry_t *mem = malloc(sizeof(entry_t));
    if (mem)
    {
        mem->ch = ch;
        mem->count = count;
        mem->next = NULL;
    }
    return mem;
}

static hashtable_t *alloc_table()
{
    hashtable_t *mem = malloc(sizeof(hashtable_t));
    if (mem)
    {
        mem->arr = malloc(INIT_CAPACITY * sizeof(entry_t*));
        if (mem->arr)
        {
            mem->capacity = INIT_CAPACITY;
            mem->len = 0;
            for (size_t i = 0 ; i < mem->capacity; i++)
            {
                mem->arr[i] = NULL;
            }
        }
        else
        {
            free(mem);
            mem = NULL;
        }
    }

    return mem;
}

hashtable_t *create_table(char *str)
{
    hashtable_t *table = alloc_table();

    if (table)
    {
        while (*str)
        {
            hashtable_put(table, *str);
            str++;
        }
    }

    return table;
}

static void free_entry(entry_t *entry)
{
    if (entry)
    {
        free(entry->next);
        free(entry);
    }
}

static void free_table_arr(entry_t **arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        free_entry(arr[i]);
    }
    free(arr);
}

void free_table(hashtable_t *table)
{
    if (table)
    {
        for (size_t i = 0; i < table->capacity; i++)
        {
            free_entry(table->arr[i]);
        }
        free(table->arr);
        free(table);
    }
}

static size_t char_hash(char ch, size_t mod)
{
    return (PRIME_CONST * ch) % mod;
}

/// Вставить элемент в не NULL массив записей
static size_t put_into(entry_t **arr, size_t capacity, char ch, size_t count)
{
    size_t add = 0;
    size_t ind = char_hash(ch, capacity);
    entry_t *entry = arr[ind];
    if (entry == NULL)
    {
        arr[ind] = alloc_entry(ch, count);
        add = 1;
    }
    else
    {
        while (entry->ch != ch && entry->next != NULL)
        {
            entry = entry->next;
        }
        if (entry->ch == ch)
        {
            entry->count += count;
        }
        else if (entry->next == NULL)
        {
            entry->next = alloc_entry(ch, count);
            add = 1;
        }
    }
    return add;
}

/// рехеширование не NULL таблицы
static void rehash(hashtable_t *table)
{
    size_t new_capacity = table->capacity * 2;
    entry_t **new_arr = malloc(new_capacity * sizeof(entry_t*));
    if (new_arr)
    {
        for (size_t i = 0; i < new_capacity; i++)
        {
            new_arr[i] = NULL;
        }

        entry_t *temp;
        for (size_t i = 0; i < table->capacity; i++)
        {
            temp = table->arr[i];
            while (temp != NULL)
            {
                put_into(new_arr, new_capacity, temp->ch, temp->count);
                temp = temp->next;
            }
        }

        free_table_arr(table->arr, table->capacity);
        table->capacity = new_capacity;
        table->arr = new_arr;
    }
}

void hashtable_put(hashtable_t *table, char ch)
{
    if (table)
    {
        table->len += put_into(table->arr, table->capacity, ch, 1);

        if (table->len >= table->capacity * REHASH_FACTOR)
        {
            rehash(table);
        }
    }
}

/// Поиск в записи по символу в хеш-таблице с возвратом числа сравнений
entry_t *hashtable_find_get_compares(hashtable_t *table, char ch, size_t *cmp_count)
{
    entry_t *entry = NULL;
    if (table)
    {
        size_t ind = char_hash(ch, table->capacity);
        entry = table->arr[ind];
        *cmp_count = 1;
        while (entry && entry->ch != ch)
        {
            (*cmp_count)++;
            entry = entry->next;
        }
    }
    return entry;
}

entry_t *hashtable_find(hashtable_t *table, char ch)
{
    entry_t *entry = NULL;
    if (table)
    {
        size_t ind = char_hash(ch, table->capacity);
        entry = table->arr[ind];
        while (entry && entry->ch != ch)
        {
            entry = entry->next;
        }
    }
    return entry;
}

void hashtable_remove(hashtable_t *table, char ch)
{
    if (table)
    {
        size_t ind = char_hash(ch, table->capacity);

        entry_t *cur = table->arr[ind];
        entry_t *prev = NULL;
        while (cur != NULL && cur->ch != ch)
        {
            prev = cur;
            cur = cur->next;
        }

        if (cur != NULL)
        {
            if (prev == NULL)
            {
                table->arr[ind] = cur->next;
            }
            else
            {
                prev->next = cur->next;
                cur->next = NULL;
            }

            free(cur);
            table->len--;
        }
    }
}

char get_entry_char(const entry_t *entry)
{
    return entry->ch;
}

size_t get_entry_count(const entry_t *entry)
{
    return entry->count;
}

static void print_entry(const entry_t *entry)
{
    if (entry)
    {
        printf("|   '%1c'  | %6zu |\n", entry->ch, entry->count);
        print_entry(entry->next);
    }
}

void print_table(hashtable_t *table)
{
    if (table)
    {
        printf("| %6s | %6s |\n", "Символ", "Кол-во");
        for (size_t i = 0; i < table->capacity; i++)
        {
            printf("| Ячейка | #%4zu  |\n", i);
            print_entry(table->arr[i]);
        }
    }
}

float hashtable_avg_cmp(hashtable_t *table)
{
    if (!table)
    {
        return 0;
    }
    size_t total_cmp = 0;
    for (size_t i = 0; i < table->capacity; i++)
    {
        entry_t *cur = table->arr[i];
        size_t add = 0;
        while (cur)
        {
            add++;
            cur = cur->next;
            total_cmp += add;
        }
    }
    return (float) total_cmp / (float) table->len;
}

size_t get_len(hashtable_t *table)
{
    if (table)
    {
        return table->len;
    }
    return 0;
}

size_t hashtable_sizeof(hashtable_t *table)
{
    size_t size = 0;
    if (table)
    {
        size += sizeof(hashtable_t);
        size += table->capacity * sizeof(entry_t*);
        size += table->len * sizeof(entry_t);
    }
    return size;
}

/// Удалить повторяющиеся
void hashtable_remove_repeating(hashtable_t *table)
{
    if (!table)
    {
        return;
    }

    entry_t *all = malloc(table->len * sizeof(entry_t));
    size_t index = 0;
    for (size_t i = 0; i < table->capacity; i++)
    {
        entry_t *cur = table->arr[i];
        while (cur)
        {
            entry_t temp = { cur->ch, cur->count, NULL };
            all[index++] = temp;
            cur = cur->next;
        }
    }

    for (size_t i = 0; i < index; i++)
    {
        entry_t cur = all[i];
        if (cur.count > 1)
        {
            hashtable_remove(table, cur.ch);
        }
    }
    free(all);
}