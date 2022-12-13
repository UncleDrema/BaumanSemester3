//
// Created by archdrema on 11/25/22.
//

#ifndef __TREE_H
#define __TREE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct tree_t tree_t;

/// Получить значение символа из узла
char get_value(const tree_t *node);

/// Получить число вхождений символа из узла
size_t get_count(const tree_t *node);

/// Создание дерева на основе строки
tree_t *create_tree(char *str);

/// Освобождение памяти, выделенной под дерево
void free_tree(tree_t *tree);

/// Постфиксный обход дерева
void traverse_post(tree_t *tree, void (*apply)(tree_t *, void *), void *acc);

/// Префиксный обход дерева
void traverse_pre(tree_t *tree, void (*apply)(tree_t *, void *), void *acc);

/// Инфиксный обход дерева
void traverse_in(tree_t *tree, void (*apply)(tree_t *, void *), void *acc);

/// Вставка символа в дерево
tree_t *tree_insert(tree_t *tree, char ch);

/// Удаление символа из дерева
tree_t *tree_remove(tree_t *tree, char ch);

/// Поиск узла в дереве
tree_t *tree_find(tree_t *tree, char ch);

/// Вывод дерева при помощи утилиты graphviz
void show_tree(tree_t *tree);

/// Копия дерева
tree_t *copy_tree(tree_t *tree);

/// Копия дерева без повторяющихся элементов
tree_t *tree_without_repeating(tree_t *tree);

#endif
