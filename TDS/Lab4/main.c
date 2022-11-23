//
// Created by archdrema on 11/10/22.
//

#include <stddef.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "err.h"
#include "stack.h"
#include "stack_arr.h"
#include "utils.h"
#include "stack_list.h"
#include "bench.h"

#define MENU_SIZE 10
#define RANGE(type, i, max) for (type i = 0; i < max; i++)
typedef void* void_ptr;

arr_stack_def(void_ptr)
arr_stack_impl(void_ptr)

list_stack_def(void_ptr)
list_stack_impl(void_ptr)

static void print_stack_arr(stack_name(arr, void_ptr) *stack)
{
    if (stack)
    {
        void_ptr *cur = stack->ps;
        while (cur && cur >= stack->arr)
        {
            printf("%p\n", *cur);
            cur--;
        }
    }
}

static void print_stack_list(stack_name(list, void_ptr) *stack)
{
    if (stack)
    {
        node_name(void_ptr) *cur = stack->top;
        while (cur)
        {
            printf("%p\n", cur->value);
            cur = cur->prev;
        }
    }
}

int main(void)
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    int mode;
    bool stop = false;
    bool dont_stop = true;

    stack_name(arr, void_ptr) *arr_stack = NULL;
    stack_name(list, void_ptr) *list_stack = NULL;

    while (!stop)
    {
        if (!dont_stop) {
            printf("Нажмите Enter, чтобы продолжить...");
            skip_to_nl(stdin);
        }
        dont_stop = false;

        char *menu[MENU_SIZE] = {
                "Создать стек на основе списка заданного размера",
                "Создать стек на основе массива заданного размера",
                "Создать стек на основе массива заданного размера (заполнить случайно)",
                "Произвести замеры эффективности стеков (оба стека должны быть заданы, операция опустошит их!)",
                "Добавить элемент в стек на основе списка",
                "Добавить элемент в стек на основе массива",
                "Удалить элемент из стека на основе списка",
                "Удалить элемент из стека на основе массива",
                "Просмотреть информацию о стеке на основе списка",
                "Просмотреть информацию о стеке на основе массива"
        };
        RANGE(int, i, MENU_SIZE)
        {
            printf("%d. %s\n", i + 1, menu[i]);
        }

        printf("0. Выход из программы\n");
        puts(arr_stack == NULL ? "Стек на основе массива не задан!" : "Стек на основе массива задан!");
        puts(list_stack == NULL ? "Стек на основе списка не задан!" : "Стек на основе списка задан!");
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
                size_t temp;
                printf("Введите длину стека: ");
                if (scanf("%zu", &temp) != 1)
                {
                    puts("Ошибка ввода размера!");
                    break;
                }
                skip_to_nl(stdin);

                if (list_stack)
                {
                    stack_free(list, void_ptr)(list_stack);
                    list_stack = NULL;
                }

                list_stack = stack_alloc(list, void_ptr)();
                node_name(void_ptr) *node;
                RANGE(size_t, i, temp)
                {
                    stack_push(list, void_ptr)(list_stack, NULL);
                    list_stack->top->value = list_stack->top;
                }
                puts("Стек создан!");
                break;
            }
            case 2:
            {
                size_t temp;
                printf("Введите длину стека: ");
                if (scanf("%zu", &temp) != 1)
                {
                    puts("Ошибка ввода размера!");
                    break;
                }
                skip_to_nl(stdin);

                if (arr_stack)
                {
                    stack_free(arr, void_ptr)(arr_stack);
                    arr_stack = NULL;
                }

                arr_stack = stack_alloc(arr, void_ptr)();
                void_ptr value;
                RANGE(size_t, i, temp)
                {
                    printf("Введите значение указателя в hex-формате (0x...): ");
                    if (scanf("%p", &value) != 1)
                    {
                        printf("Ошибка ввода! Попробуйте ещё раз: ");
                        i--;
                    }
                    else
                    {
                        stack_push(arr, void_ptr)(arr_stack, value);
                    }
                }
                puts("Стек создан!");
                break;
            }
            case 3:
            {
                size_t temp;
                printf("Введите длину стека: ");
                if (scanf("%zu", &temp) != 1)
                {
                    puts("Ошибка ввода размера!");
                    break;
                }
                skip_to_nl(stdin);

                if (arr_stack)
                {
                    stack_free(arr, void_ptr)(arr_stack);
                    arr_stack = NULL;
                }

                arr_stack = stack_alloc(arr, void_ptr)();
                RANGE(size_t, i, temp)
                {
                    stack_push(arr, void_ptr)(arr_stack, (void_ptr) (long) rand());
                }
                puts("Стек создан!");
                break;
            }
            case 4:
            {
                if ((!list_stack || stack_len(list, void_ptr)(list_stack) == 0) ||
                    (!arr_stack || stack_len(list, void_ptr)(list_stack) == 0))
                {
                    puts("Один из стеков не задан или пуст!");
                    break;
                }

                const size_t len_repeats = 10000;
                const size_t pp_repeats = 10000000;
                size_t arr_len = stack_len(arr, void_ptr)(arr_stack);
                size_t list_len = stack_len(list, void_ptr)(list_stack);

                double mean_list_pp, mean_arr_pp, mean_list_len, mean_arr_len;
                ms_t total_arr_len, total_list_len, total_arr_pp, total_list_pp, total_arr_drop, total_list_drop;
                ms_clock_t *arr_clock = get_clock(), *list_clock = get_clock();
                void_ptr temp_el_ptr;
                volatile size_t temp_len;

                puts("Замеряем эффективность получения длины стека...");
                RANGE(size_t, i, len_repeats)
                {
                    clock_start(arr_clock);
                    temp_len = stack_len(arr, void_ptr)(arr_stack);
                    clock_stop(arr_clock);
                    clock_start(list_clock);
                    temp_len = stack_len(list, void_ptr)(list_stack);
                    clock_stop(list_clock);
                }

                total_arr_len = clock_total(arr_clock);
                total_list_len = clock_total(list_clock);
                mean_arr_len = mean_ms(total_arr_len, len_repeats);
                mean_list_len = mean_ms(total_list_len, len_repeats);
                clock_reset(arr_clock);
                clock_reset(list_clock);

                puts("Замеряем эффективность изъятия + помещения элемента в стек...");
                RANGE(size_t, i, pp_repeats)
                {
                    clock_start(arr_clock);
                    stack_pop(arr, void_ptr)(arr_stack, &temp_el_ptr);
                    stack_push(arr, void_ptr)(arr_stack, temp_el_ptr);
                    clock_stop(arr_clock);
                    clock_start(list_clock);
                    stack_pop(list, void_ptr)(list_stack, &temp_el_ptr);
                    stack_push(list, void_ptr)(list_stack, temp_el_ptr);
                    clock_stop(list_clock);
                }

                total_arr_pp = clock_total(arr_clock);
                total_list_pp = clock_total(list_clock);
                mean_arr_pp = mean_ms(total_arr_pp, pp_repeats);
                mean_list_pp = mean_ms(total_list_pp, pp_repeats);
                clock_reset(arr_clock);
                clock_reset(list_clock);

                stack_shrink(void_ptr)(arr_stack);
                size_t arr_size = stack_sizeof(arr, void_ptr)(arr_stack);
                size_t list_size = stack_sizeof(list, void_ptr)(list_stack);

                puts("Замеряем время очистки стека...");

                clock_start(arr_clock);
                while (stack_pop(arr, void_ptr)(arr_stack, &temp_el_ptr) == OK);
                stack_free(arr, void_ptr)(arr_stack);
                arr_stack = NULL;
                clock_stop(arr_clock);
                clock_start(list_clock);
                while (stack_pop(list, void_ptr)(list_stack, &temp_el_ptr) == OK);
                stack_free(list, void_ptr)(list_stack);
                list_stack = NULL;
                clock_stop(list_clock);

                total_arr_drop = clock_total(arr_clock);
                total_list_drop = clock_total(list_clock);

                printf("Было произведено %zu замеров для длины и %zu замеров для pop/push, размер стека на основе массива - %zu, стека на основе списка - %zu, результат:\n", len_repeats, pp_repeats, arr_len, list_len);
                printf("| Тип    | Длина (total)   | pop/push (total) | Длина (av)  | pop/push (av)  | Очистка         | Память         |\n");
                printf("| Массив | %12llu ms | %12llu ms  | %2.6f    | %2.8f     | %12llu ms | %8zu bytes |\n", total_arr_len, total_arr_pp, mean_arr_len, mean_arr_pp, total_arr_drop, arr_size);
                printf("| Список | %12llu ms | %12llu ms  | %2.6f    | %2.8f     | %12llu ms | %8zu bytes |\n", total_list_len, total_list_pp, mean_list_len, mean_list_pp, total_list_drop, list_size);

                free_clock(arr_clock);
                free_clock(list_clock);
                break;
            }
            case 5:
            {
                if (!list_stack)
                {
                    puts("Стек не задан!");
                    break;
                }
                err_t rc = stack_push(list, void_ptr)(list_stack, NULL);
                list_stack->top->value = list_stack->top;
                if (rc == OK)
                {
                    puts("Элемент добавлен!");
                }
                else
                {
                    puts("Элемент не может быть добавлен! Переполнение стека.");
                }
                break;
            }
            case 6:
            {
                if (!arr_stack)
                {
                    puts("Стек не задан!");
                    break;
                }
                void_ptr value;
                printf("Введите значение указателя в hex-формате (0x...): ");
                if (scanf("%p", &value) != 1)
                {
                    puts("Ошибка ввода!");
                    break;
                }
                err_t rc = stack_push(arr, void_ptr)(arr_stack, value);
                if (rc == OK)
                {
                    puts("Элемент добавлен!");
                }
                else
                {
                    puts("Элемент не может быть добавлен! Переполнение стека.");
                    break;
                }
                break;
            }
            case 7:
            {
                if (!list_stack)
                {
                    puts("Стек не задан!");
                    break;
                }

                void_ptr el;
                err_t rc = stack_pop(list, void_ptr)(list_stack, &el);
                if (rc != OK)
                {
                    puts("Элемент не может быть удалён, стек пуст!");
                }
                else
                {
                    printf("Элемент удалён, значение: %p\n", el);
                }
                break;
            }
            case 8:
            {
                if (!arr_stack)
                {
                    puts("Стек не задан!");
                    break;
                }

                void_ptr el;
                err_t rc = stack_pop(arr, void_ptr)(arr_stack, &el);
                if (rc != OK)
                {
                    puts("Элемент не может быть удалён, стек пуст!");
                }
                else
                {
                    printf("Элемент удалён, значение: %p\n", el);
                }
                break;
            }
            case 9:
            {
                if (!list_stack)
                {
                    puts("Стек не задан!");
                    break;
                }
                size_t len = stack_len(list, void_ptr)(list_stack);
                if (len > 0)
                {
                    puts("Содержимое стека (от вершины к низу):");
                    print_stack_list(list_stack);
                    void_ptr top;
                    stack_peek(list, void_ptr)(list_stack, &top);
                    printf("Длина стека: %zu, верхний элемент: %p\n", len, top);
                }
                else
                {
                    puts("Стек пуст!");
                }
                break;
            }
            case 10:
            {
                if (!arr_stack)
                {
                    puts("Стек не задан!");
                    break;
                }
                printf("arr: %p ps: %p end: %p\n", arr_stack->arr, arr_stack->ps, arr_stack->end);
                size_t len = stack_len(arr, void_ptr)(arr_stack);
                if (len > 0)
                {
                    puts("Содержимое стека (от вершины к низу):");
                    print_stack_arr(arr_stack);
                    void_ptr top;
                    stack_peek(arr, void_ptr)(arr_stack, &top);
                    printf("Длина стека: %zu, верхний элемент: %p\n", len, top);
                }
                else
                {
                    puts("Стек пуст!");
                }
                break;
            }
            case 0:
                stop = true;
                break;
        }
    }

    if (arr_stack)
    {
        stack_free(arr, void_ptr)(arr_stack);
    }

    if (list_stack)
    {
        stack_free(list, void_ptr)(list_stack);
    }

    return 0;
}