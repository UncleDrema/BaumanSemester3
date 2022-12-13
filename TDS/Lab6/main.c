//
// Created by archdrema on 11/17/22.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "utils.h"
#include "console_colors.h"
#include "tree.h"
#include "bench.h"

#define MENU_SIZE 10

static void print_element(tree_t *tree, void *not_used)
{
    printf("\"%c\": %zu\n", get_value(tree), get_count(tree));
    (void) not_used;
}

int main(void)
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    int mode;
    bool stop = false;
    bool dont_stop = true;
    char *cur_str = NULL;
    tree_t *cur_tree = NULL;

    while (!stop)
    {
        if (!dont_stop)
        {
            puts("Нажмите Enter, чтобы продолжить...");
            skip_to_nl(stdin);
        }
        dont_stop = false;

        char *menu[MENU_SIZE] = {
                "Построить дерево поиска по строке",
                "Вывести дерево на экран (" RED "левый" GREEN " правый " BLUE ">1" RESET ")",
                "Удалить повторяющиеся буквы из строки и дерева",
                "Вывести элементы дерева при постфиксном обходе",
                "Сравнить время удаления повторяющихся букв из текущих дерева и строки",
                "Сгенерировать случайную строку заданного размера и создать дерево на её основе",
                "Добавить символ в дерево",
                "Удалить символ из дерева",
                "Найти символ в дереве",
                "Измерить время обработки узла в дереве"
        };
        for (int i = 0; i < MENU_SIZE; i++)
        {
            printf("%d. %s\n", i + 1, menu[i]);
        }

        printf("0. Выход из программы\n");
        printf("Дерево и строка %s!\n", (cur_tree == NULL ? RED "не заданы" RESET : GREEN "заданы" RESET));
        if (cur_str)
        {
            printf("Строка: \"%s\"\n", cur_str);
        }
        printf("Выберите пункт меню: ");
        if (scanf("%d", &mode) != 1 || mode < 0 || mode > MENU_SIZE) {
            skip_to_nl(stdin);
            continue;
        }
        skip_to_nl(stdin);

        switch (mode)
        {
            case 1:
            {
                if (cur_str)
                {
                    free(cur_str);
                    cur_str = NULL;
                }
                if (cur_tree)
                {
                    free_tree(cur_tree);
                    cur_tree = NULL;
                }
                printf("Введите строку (допускаются английские буквы, цифры и другие символы ASCII): ");

                size_t temp;
                ssize_t res = getline(&cur_str, &temp, stdin);

                if (res == -1 || temp < 2)
                {
                    puts("Ошибка ввода!");
                    free(cur_str);
                    cur_str = NULL;
                    break;
                }

                *strrchr(cur_str, '\n') = '\0';

                cur_tree = create_tree(cur_str);
                if (!cur_tree)
                {
                    free(cur_str);
                    cur_str = NULL;
                    cur_tree = NULL;
                }
                dont_stop = true;
                break;
            }
            case 2:
            {
                if (!cur_tree)
                {
                    puts("Дерево не задано или пустое!");
                    break;
                }

                show_tree(cur_tree);
                dont_stop = true;
                break;
            }
            case 3:
            {
                if (!cur_tree || !cur_str)
                {
                    puts("Дерево и строка не заданы!");
                    break;
                }

                tree_t *new_tree = tree_without_repeating(cur_tree);
                char *new_str = str_without_repeating(cur_str);

                free_tree(cur_tree);
                free(cur_str);

                cur_str = new_str;
                cur_tree = new_tree;
                dont_stop = true;
                break;
            }
            case 4:
            {
                if (!cur_tree)
                {
                    puts("Дерево не задано!");
                    break;
                }

                traverse_post(cur_tree, print_element, NULL);
                break;
            }
            case 5:
            {
                if (!cur_tree || !cur_str)
                {
                    puts("Дерево и строка не заданы!");
                    break;
                }

                ms_clock_t *clock = get_clock();
                double tree_time = 0, str_time = 0;
                ms_t tree_total = 0, str_total = 0;
                volatile char *volatile test_str = NULL;
                volatile tree_t *volatile test_tree = NULL;

                size_t times = 1000000;

                puts("Измеряем производительность для строки...");
                clock_start(clock);
                for (size_t i = 0; i < times; i++)
                {
                    test_str = str_without_repeating(cur_str);
                    clock_stop(clock);
                    free(test_str);
                    clock_start(clock);
                }
                clock_stop(clock);
                str_total = clock_total(clock);
                str_time = mean_ms(str_total, times);

                clock_reset(clock);

                puts("Измеряем производительность для дерева поиска...");
                clock_start(clock);
                for (size_t i = 0; i < times; i++)
                {
                    test_tree = tree_without_repeating(cur_tree);
                    clock_stop(clock);
                    free_tree(test_tree);
                    clock_start(clock);
                }
                clock_stop(clock);
                tree_total = clock_total(clock);
                tree_time = mean_ms(tree_total, times);

                printf("Произведено %zu замеров удаления повторяющихся букв из строки и дерева поиска, результат:\n",
                       times);
                printf("Строка: %8llu мс. всего, %.4f мс. в среднем\n", str_total, str_time);
                printf("Дерево: %8llu мс. всего, %.4f мс. в среднем\n", tree_total, tree_time);

                free_clock(clock);
                break;
            }
            case 6:
            {
                if (cur_str)
                {
                    free(cur_str);
                    cur_str = NULL;
                }
                if (cur_tree)
                {
                    free_tree(cur_tree);
                    cur_tree = NULL;
                }
                size_t size;
                printf("Введите размер строки: ");
                if (scanf("%zu", &size) != 1)
                {
                    puts("Ошибка ввода!");
                }

                cur_str = rand_str(size);
                cur_tree = create_tree(cur_str);
                dont_stop = true;
                break;
            }
            case 7:
            {
                char ch;
                printf("Введите символ (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                cur_tree = tree_insert(cur_tree, ch);
                puts("Символ добавлен!");
                dont_stop = true;
                break;
            }
            case 8:
            {
                char ch;
                printf("Введите символ (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                cur_tree = tree_remove(cur_tree, ch);
                puts("Символ удалён!");
                dont_stop = true;
                break;
            }
            case 9:
            {
                char ch;
                printf("Введите символ (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                tree_t *found = tree_find(cur_tree, ch);
                if (!found)
                {
                    puts("Символ не найден в дереве!");
                }
                else
                {
                    printf("Символ \"%c\" найден с количеством повторений: %zu\n", get_value(found), get_count(found));
                }
                break;
            }
            case 10:
            {
                char ch;
                printf("Введите символ (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                ms_clock_t *clock = get_clock();
                double tree_time = 0;
                volatile tree_t * volatile find_tree = NULL;
                ms_t tree_total = 0;

                size_t times = 1000000;

                puts("Замеряем время доступа к узлу...");
                clock_start(clock);
                for (size_t i = 0; i < times; i++)
                {
                    find_tree = tree_find(cur_tree, ch);
                }
                clock_stop(clock);
                tree_total = clock_total(clock);
                tree_time = mean_ms(tree_total, times);

                printf("Поиск элемента произведён %zu раз:\n", times);
                if (find_tree != NULL)
                {
                    printf("Время поиска символа \"%c\": %8llu мс. всего, %.8f мс. в среднем\n", get_value(find_tree), tree_total, tree_time);
                }
                else
                {
                    printf("Время поиска символа \"%c\": %8llu мс. всего, %.8f мс. в среднем, символ не найден!\n", ch, tree_total, tree_time);
                }
                break;
            }
            case 0:
                stop = true;
                break;
        }
    }

    return 0;
}