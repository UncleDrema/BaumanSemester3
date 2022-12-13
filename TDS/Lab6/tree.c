//
// Created by archdrema on 11/25/22.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct tree_t
{
    char key;
    size_t count;
    tree_t *left;
    tree_t *right;
};

static tree_t *alloc_tree(char ch)
{
    tree_t *mem = malloc(sizeof(tree_t));
    if (mem)
    {
        mem->key = ch;
        mem->count = 1;
        mem->left = NULL;
        mem->right = NULL;
    }
    return mem;
}

char get_value(const tree_t *node)
{
    return node->key;
}

size_t get_count(const tree_t *node)
{
    return node->count;
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

    if (ch < tree->key)
    {
        tree->left = tree_insert(tree->left, ch);
    }
    else if (ch > tree->key)
    {
        tree->right = tree_insert(tree->right, ch);
    }
    else
    {
        tree->count++;
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
    if (ch < tree->key)
    {
        tree->left = tree_remove(tree->left, ch);
    }
    else if (ch > tree->key)
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

tree_t *tree_find(tree_t *tree, char ch)
{
    if (!tree)
    {
        return NULL;
    }

    if (ch < tree->key)
    {
        return tree_find(tree->left, ch);
    }
    else if (ch > tree->key)
    {
        return tree_find(tree->right, ch);
    }
    else
    {
        return tree;
    }
}

static void save_to_graphviz(tree_t *tree, void *file)
{
    FILE *f = file;

    char ch = tree->key;
    if (ch == '<' || ch == '>' || ch == '&')
    {
        ch = '?';
    }
    fprintf(f, "%d [color=%s;label=<\"%c\"<br/>x%zu>]\n", tree->key, tree->count > 1 ? "blue" : "black", ch, tree->count);
    if (tree->left)
    {
        fprintf(f, "%d -> %d [color=\"red\"]\n", tree->key, tree->left->key);
    }
    if (tree->right)
    {
        fprintf(f, "%d -> %d [color=\"green\"]\n", tree->key, tree->right->key);
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
        tree_t *copy = alloc_tree(tree->key);
        copy->count = tree->count;
        copy->left = copy_tree(tree->left);
        copy->right = copy_tree(tree->right);
        return copy;
    }

    return NULL;
}

static void fill_freqs(tree_t *tree, void *ptr)
{
    size_t *buf = ptr;

    buf[(unsigned char)tree->key] = tree->count;
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