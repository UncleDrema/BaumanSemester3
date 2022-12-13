//
// Created by archdrema on 11/25/22.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct tree_data
{
    char key;
    size_t count;
} tree_data;

struct tree_t
{
    tree_data data;
    tree_t *left;
    tree_t *right;
};

static tree_t *alloc_tree(char ch)
{
    tree_t *mem = malloc(sizeof(tree_t));
    if (mem)
    {
        mem->data.key = ch;
        mem->data.count = 1;
        mem->left = NULL;
        mem->right = NULL;
    }
    return mem;
}

char get_char(const tree_t *node)
{
    return node->data.key;
}

size_t get_count(const tree_t *node)
{
    return node->data.count;
}

tree_t *create_tree(char *str)
{
    tree_t *tree = NULL;
    while (*str)
    {
        tree = tree_insert(tree, *str);
        str++;
    }

    return tree;
}

static void free_node(tree_t *node, void *not_used)
{
    free(node);
    (void) not_used;
}

void free_tree(tree_t *tree)
{
    traverse_post(tree, free_node, NULL);
}

void traverse_post(tree_t *tree, void (*apply)(tree_t *, void *), void *acc)
{
    if (tree)
    {
        traverse_post(tree->left, apply, acc);
        traverse_post(tree->right, apply, acc);
        apply(tree, acc);
    }
}

void traverse_pre(tree_t *tree, void (*apply)(tree_t *, void *), void *acc)
{
    if (tree)
    {
        traverse_post(tree->left, apply, acc);
        apply(tree, acc);
        traverse_post(tree->right, apply, acc);
    }
}

void traverse_in(tree_t *tree, void (*apply)(tree_t *, void *), void *acc)
{
    if (tree)
    {
        traverse_post(tree->left, apply, acc);
        apply(tree, acc);
        traverse_post(tree->right, apply, acc);
    }
}

tree_t *tree_insert(tree_t *tree, char ch)
{
    if (!tree)
    {
        return alloc_tree(ch);
    }

    if (ch < tree->data.key)
    {
        tree->left = tree_insert(tree->left, ch);
    }
    else if (ch > tree->data.key)
    {
        tree->right = tree_insert(tree->right, ch);
    }
    else
    {
        tree->data.count++;
    }

    return tree;
}

static tree_t *join(tree_t *l, tree_t *r)
{
    if (!l)
    {
        return r;
    }
    if (!r)
    {
        return l;
    }

    l->right = join(l->right, r);
    return l;
}

tree_t *tree_remove(tree_t *tree, char ch)
{
    if (!tree)
    {
        return tree;
    }
    if (ch < tree->data.key)
    {
        tree->left = tree_remove(tree->left, ch);
    }
    else if (ch > tree->data.key)
    {
        tree->right = tree_remove(tree->right, ch);
    }
    else
    {
        tree_t *joined = join(tree->left, tree->right);
        free(tree);
        return joined;
    }

    return tree;
}

static tree_t *tree_find_base(tree_t *tree, char ch, size_t *cmp_count)
{
    if (!tree)
    {
        return NULL;
    }

    if (cmp_count)
    {
        (*cmp_count)++;
    }
    if (ch < tree->data.key)
    {
        return tree_find_base(tree->left, ch, cmp_count);
    }
    else if (ch > tree->data.key)
    {
        return tree_find_base(tree->right, ch, cmp_count);
    }
    else
    {
        return tree;
    }
}

tree_t *tree_find(tree_t *tree, char ch)
{
    return tree_find_base(tree, ch, NULL);
}

/// Поиск узла в дереве с возвратом числа сравнений
tree_t *tree_find_get_compares(tree_t *tree, char ch, size_t *cmp_count)
{
    if (!cmp_count)
    {
        return tree_find(tree, ch);
    }

    *cmp_count = 0;
    return tree_find_base(tree, ch, cmp_count);
}

static void save_to_graphviz(tree_t *tree, void *file)
{
    FILE *f = file;

    char ch = tree->data.key;
    if (ch == '<' || ch == '>' || ch == '&')
    {
        ch = '?';
    }
    fprintf(f, "%d [color=%s;label=<\"%c\"<br/>x%zu>]\n", tree->data.key, tree->data.count > 1 ? "blue" : "black", ch, tree->data.count);
    if (tree->left)
    {
        fprintf(f, "%d -> %d [color=\"red\"]\n", tree->data.key, tree->left->data.key);
    }
    if (tree->right)
    {
        fprintf(f, "%d -> %d [color=\"green\"]\n", tree->data.key, tree->right->data.key);
    }
}

#define FILENAME "graph.dot"

void show_tree(tree_t *tree)
{
    FILE *f = fopen(FILENAME, "w");

    if (f)
    {
        fputs("digraph G {\n", f);

        traverse_pre(tree, save_to_graphviz, f);

        fputs("}", f);
        fclose(f);

        system("dot " FILENAME " -Tpng | display; rm " FILENAME);
    }
}

tree_t *copy_tree(tree_t *tree)
{
    if (tree)
    {
        tree_t *copy = alloc_tree(tree->data.key);
        copy->data.count = tree->data.count;
        copy->left = copy_tree(tree->left);
        copy->right = copy_tree(tree->right);
        return copy;
    }

    return NULL;
}

static void fill_freqs(tree_t *tree, void *ptr)
{
    size_t *buf = ptr;

    buf[(unsigned char)tree->data.key] = tree->data.count;
}

tree_t *tree_without_repeating(tree_t *tree)
{
    tree_t *res = copy_tree(tree);
    size_t all_chars[UCHAR_MAX + 1];
    for (int i = 0; i <= UCHAR_MAX; i++)
    {
        all_chars[i] = 0;
    }

    traverse_in(res, fill_freqs, all_chars);
    for (int i = 0; i <= UCHAR_MAX; i++)
    {
        if (all_chars[i] > 1)
        {
            res = tree_remove(res, (char) i);
        }
    }

    return res;
}

static void count_nodes(tree_t *node, void *acc)
{
    int *counter = acc;
    (*counter)++;
}

static void put_nodes(tree_t *node, void *acc)
{
    void **buf = acc;
    int *counter = buf[0];
    tree_data **arr = buf[1];
    (*arr)[*counter] = node->data;
    (*counter)++;
}

static int cmp_data(const void *a, const void *b)
{
    const tree_data *a_data = a;
    const tree_data *b_data = b;

    return (*a_data).key - (*b_data).key;
}

static tree_t *create_balanced_tree(int n, tree_data *data)
{
    if (n <= 0)
    {
        return NULL;
    }

    int median_pos = n / 2;
    tree_data median = data[median_pos];

    tree_t *node = alloc_tree(median.key);
    node->data.count = median.count;

    node->left = create_balanced_tree(median_pos, data);
    node->right = create_balanced_tree(n - median_pos - 1, data + median_pos + 1);
    return node;
}

static tree_data *get_all_data(tree_t *tree, int *len)
{
    int counter = 0;
    traverse_pre(tree, count_nodes, &counter);
    tree_data *arr = malloc(counter * sizeof(tree_data));

    int ind = 0;
    void *buf[2] = {&ind, &arr};
    traverse_in(tree, put_nodes, buf);

    *len = counter;
    return arr;
}

tree_t *balanced_tree(tree_t *tree)
{
    int counter;
    tree_data *arr = get_all_data(tree, &counter);

    tree_t *res = create_balanced_tree(counter, arr);

    free(arr);
    return res;
}

float tree_avg_cmp(tree_t *tree)
{
    if (!tree)
    {
        return 0;
    }
    int counter;
    tree_data *arr = get_all_data(tree, &counter);

    size_t total_cmp = 0;
    for (int i = 0; i < counter; i++)
    {
        size_t temp = 0;
        tree_find_base(tree, arr[i].key, &temp);
        total_cmp += temp;
    }

    return (float) total_cmp / (float) counter;
}

size_t tree_sizeof(tree_t *tree)
{
    int count = 0;
    traverse_in(tree, count_nodes, &count);
    return count * sizeof(tree_t);
}
