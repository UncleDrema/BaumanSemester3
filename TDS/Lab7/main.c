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
#include "hashtable.h"

#define MENU_SIZE 20

int main(void)
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    int mode;
    bool stop = false;
    bool dont_stop = true;
    char *cur_str = NULL;
    tree_t *cur_tree = NULL;
    tree_t *bal_tree = NULL;
    hashtable_t *table = NULL;

    while (!stop)
    {
        if (!dont_stop)
        {
            puts("Нажмите Enter, чтобы продолжить...");
            skip_to_nl(stdin);
        }
        dont_stop = false;

        char *menu[MENU_SIZE] = {
                "Ввести строку",
                "Удалить повторяющиеся буквы из строки",
                "Сгенерировать случайную строку заданного размера",
                "Построить двоичное дерево поиска, сбалансированное дерево поиска и хеш-таблицу по строке",
                "Вывести дерево на экран (" RED "левый" GREEN " правый " BLUE ">1" RESET ")",
                "Добавить символ в дерево",
                "Удалить символ из дерева",
                "Найти символ в дереве",
                "Вывести сбалансированное дерево на экран (" RED "левый" GREEN " правый " BLUE ">1" RESET ")",
                "Добавить символ в сбалансированное дерево",
                "Удалить символ из сбалансированного дерева",
                "Найти символ в сбалансированном дереве",
                "Вывести хеш-таблицу",
                "Добавить символ в хеш-таблицу",
                "Удалить символ из хеш-таблицы",
                "Найти символ в хеш-таблице",
                "Провести анализ эффективности работы структур данных на основе текущей заданной строки",
                "Удалить повторяющиеся буквы из двоичного дерева поиска",
                "Удалить повторяющиеся буквы из сбалансированного двоичного дерева поиска",
                "Удалить повторяющиеся буквы из хеш-таблицы"
        };
        for (int i = 0; i < MENU_SIZE; i++)
        {
            printf("%d. %s\n", i + 1, menu[i]);
        }

        printf("0. Выход из программы\n");
        printf("Строка %s!\n", (cur_str == NULL ? RED "не задана" RESET : GREEN "задана" RESET));
        printf("Двоичное дерево поиска %s!\n", (cur_tree == NULL ? RED "не задано" RESET : GREEN "задано" RESET));
        printf("Сбалансированное дерево поиска %s!\n", (bal_tree == NULL ? RED "не задано" RESET : GREEN "задано" RESET));
        printf("Хеш-таблица %s!\n", (table == NULL ? RED "не задана" RESET : GREEN "задана" RESET));
        if (cur_str)
        {
            printf("Строка: \"%s\"\n", cur_str);
        }
        printf("Выберите пункт меню: ");
        if (scanf("%d", &mode) != 1 || mode < 0 || mode > MENU_SIZE)
        {
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
                dont_stop = true;
                break;
            }
            case 2:
            {
                if (!cur_str)
                {
                    puts("Строка не задана!");
                    break;
                }

                char *new_str = str_without_repeating(cur_str);
                free(cur_str);

                cur_str = new_str;
                dont_stop = true;
                break;
            }
            case 3:
            {
                if (cur_str)
                {
                    free(cur_str);
                    cur_str = NULL;
                }
                size_t size;
                printf("Введите размер строки: ");
                if (scanf("%zu", &size) != 1)
                {
                    puts("Ошибка ввода!");
                }

                cur_str = rand_str(size);
                dont_stop = true;
                break;
            }
            case 4:
            {
                if (!cur_str)
                {
                    puts("Строка не задана!");
                    break;
                }
                if (cur_tree)
                {
                    free_tree(cur_tree);
                    cur_tree = NULL;
                }
                if (bal_tree)
                {
                    free_tree(cur_tree);
                    cur_tree = NULL;
                }
                if (table)
                {
                    free_table(table);
                    table = NULL;
                }

                cur_tree = create_tree(cur_str);
                bal_tree = balanced_tree(cur_tree);
                table = create_table(cur_str);
                dont_stop = true;
                break;
            }
            case 5:
            {
                if (!cur_tree)
                {
                    puts("Дерево не задано или пустое!");
                    break;
                }

                printf("Среднее число сравнений: %f\n", tree_avg_cmp(cur_tree));
                show_tree(cur_tree);
                break;
            }
            case 6:
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
            case 7:
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
            case 8:
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
                    printf("Символ \"%c\" найден с количеством повторений: %zu\n", get_char(found), get_count(found));
                }
                break;
            }
            case 9:
            {
                if (!bal_tree)
                {
                    puts("Сбалансированное дерево не задано или пустое!");
                    break;
                }

                printf("Среднее число сравнений: %f\n", tree_avg_cmp(bal_tree));
                show_tree(bal_tree);
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

                bal_tree = tree_insert(bal_tree, ch);
                tree_t *new = balanced_tree(bal_tree);
                free_tree(bal_tree);
                bal_tree = new;
                puts("Символ добавлен!");
                dont_stop = true;
                break;
            }
            case 11:
            {
                char ch;
                printf("Введите символ (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                bal_tree = tree_remove(bal_tree, ch);
                tree_t *new = balanced_tree(bal_tree);
                free_tree(bal_tree);
                bal_tree = new;
                puts("Символ удалён!");
                dont_stop = true;
                break;
            }
            case 12:
            {
                char ch;
                printf("Введите символ (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                tree_t *found = tree_find(bal_tree, ch);
                if (!found)
                {
                    puts("Символ не найден в сбалансированном дереве!");
                }
                else
                {
                    printf("Символ \"%c\" найден с количеством повторений: %zu\n", get_char(found), get_count(found));
                }
                break;
            }
            case 13:
            {
                if (!cur_tree)
                {
                    puts("Хеш-таблица не задана!");
                    break;
                }

                printf("Число элементов: %zu, среднее число сравнений: %f\n", get_len(table), hashtable_avg_cmp(table));
                print_table(table);
                dont_stop = true;
                break;
            }
            case 14:
            {
                if (!table)
                {
                    puts("Таблица не задана!");
                    break;
                }
                char ch;
                printf("Введите символ (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                hashtable_put(table, ch);
                puts("Символ добавлен!");
                dont_stop = true;
                break;
            }
            case 15:
            {
                char ch;
                printf("Введите символ (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                hashtable_remove(table, ch);
                puts("Символ удалён!");
                dont_stop = true;
                break;
            }
            case 16:
            {
                if (!table)
                {
                    puts("Таблица не задана!");
                    break;
                }
                char ch;
                printf("Введите символ (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                entry_t *found = hashtable_find(table, ch);
                if (!found)
                {
                    puts("Символ не найден в хеш-таблице!");
                }

                else
                {
                    printf("Символ \"%c\" найден с количеством повторений: %zu\n", get_entry_char(found),get_entry_count(found));
                }
                break;
            }
            case 17:
            {
                if (!cur_str)
                {
                    puts("Строка не задана!");
                }

                tree_t *test_bin_tree = create_tree(cur_str);
                tree_t *test_bal_tree = balanced_tree(test_bin_tree);
                hashtable_t *test_hashtable = create_table(cur_str);

                char ch;
                printf("Введите символ для поиска (допускаются английские буквы, цифры и другие символы ASCII): ");
                if (scanf("%c", &ch) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                if (!tree_find(test_bal_tree, ch))
                {
                    puts("Символ отсутствует в строке!");
                    break;
                }

                size_t cmp_bin_tree = 0, cmp_bal_tree = 0, cmp_hashtable = 0;
                tree_find_get_compares(test_bin_tree, ch, &cmp_bin_tree);
                tree_find_get_compares(test_bal_tree, ch, &cmp_bal_tree);
                hashtable_find_get_compares(table, ch, &cmp_hashtable);

                ms_clock_t *clock = get_clock();

                size_t times = 100000000;
                size_t str_times = 1000000;
                ms_t total_bin_tree = 0, total_bal_tree = 0, total_hashtable = 0, total_str;
                double mean_bin_tree = 0, mean_bal_tree = 0, mean_hashtable = 0, mean_str;
                printf("Проводится %zu замеров по поиску символа в СД и %zu для поиска в строке\n", times, str_times);

                volatile entry_t volatile *temp_entry;
                volatile tree_t volatile *temp_tree;
                volatile size_t temp_str;

                puts("Измеряем эффективность бинарного дерева поиска");
                clock_start(clock);
                for (size_t i = 0; i < times; i++)
                {
                    temp_tree = tree_find(test_bin_tree, ch);
                }
                clock_stop(clock);
                total_bin_tree = clock_total(clock);
                mean_bin_tree = mean_ms(total_bin_tree, times);

                clock_reset(clock);

                puts("Измеряем эффективность сбалансированного бинарного дерева поиска");
                clock_start(clock);
                for (size_t i = 0; i < times; i++)
                {
                    temp_tree = tree_find(test_bal_tree, ch);
                }
                clock_stop(clock);
                total_bal_tree = clock_total(clock);
                mean_bal_tree = mean_ms(total_bal_tree, times);

                clock_reset(clock);

                puts("Измеряем эффективность хеш-таблицы");
                clock_start(clock);
                for (size_t i = 0; i < times; i++)
                {
                    temp_entry = hashtable_find(test_hashtable, ch);
                }
                clock_stop(clock);
                total_hashtable = clock_total(clock);
                mean_hashtable = mean_ms(total_hashtable, times);

                clock_reset(clock);

                puts("Измеряем эффективность поиска в строке");
                clock_start(clock);
                for (size_t i = 0; i < str_times; i++)
                {
                    count_str(cur_str, ch, &temp_str);
                }
                clock_stop(clock);
                total_str = clock_total(clock);
                mean_str = mean_ms(total_str, str_times);

                size_t bin_tree_size = tree_sizeof(test_bin_tree);
                size_t bal_tree_size = tree_sizeof(test_bal_tree);
                size_t hashtable_size = hashtable_sizeof(test_hashtable);
                float avg_bin_tree = tree_avg_cmp(test_bin_tree);
                float avg_bal_tree = tree_avg_cmp(test_bal_tree);
                float avg_hashtable = hashtable_avg_cmp(test_hashtable);

                printf("| Структура данных    | Время всего (мс) | Время среднее (мс) | Память (байт) | Число сравнений | Среднее число сравнений |\n");
                printf("| Бинарное ДП         | %16llu | %18.5f | %13zu | %15zu | %23.7f |\n", total_bin_tree, mean_bin_tree, bin_tree_size, cmp_bin_tree, avg_bin_tree);
                printf("| Сбалансированное ДП | %16llu | %18.5f | %13zu | %15zu | %23.7f |\n", total_bal_tree, mean_bal_tree, bal_tree_size, cmp_bal_tree, avg_bal_tree);
                printf("| Хеш-таблица         | %16llu | %18.5f | %13zu | %15zu | %23.7f |\n", total_hashtable, mean_hashtable, hashtable_size, cmp_hashtable, avg_hashtable);
                printf("| Строка              | %16llu | %18.5f | %13zu avg_hashtable| %15zu | %23.7f |\n", total_str, mean_str, (size_t) 0, strlen(cur_str), (float) strlen(cur_str));

                free_clock(clock);
                break;
            }
            case 18:
            {
                if (!cur_tree)
                {
                    puts("Дерево не задано!");
                    break;
                }

                tree_t *new = tree_without_repeating(cur_tree);
                free_tree(cur_tree);
                cur_tree = new;
                break;
            }
            case 19:
            {
                if (!bal_tree)
                {
                    puts("Дерево не задано!");
                    break;
                }

                {
                    tree_t *new = tree_without_repeating(create_tree(str_without_repeating(cur_str)));
                    free_tree(bal_tree);
                    bal_tree = new;
                }
                {
                    tree_t *new = balanced_tree(bal_tree);
                    free_tree(bal_tree);
                    bal_tree = new;
                }
                break;
            }
            case 20:
            {
                if (!table)
                {
                    puts("Хеш-таблица не задана!");
                    break;
                }

                hashtable_remove_repeating(table);
                break;
            }
            case 0:
                stop = true;
                break;
        }
    }

    return 0;
}