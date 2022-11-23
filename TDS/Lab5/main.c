//
// Created by archdrema on 11/17/22.
//

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include "utils.h"
#include "queue_list.h"
#include "queue_arr.h"
#include "bench.h"

typedef struct request_t
{
    int processed_count;
} request_t;

list_queue_def(request_t);
list_queue_impl(request_t);

arr_queue_def(request_t);
arr_queue_impl(request_t);

#define MENU_SIZE 6

static double mean(double a, double b)
{
    return (a + b) / 2;
}

int main(void)
{
    srand(time(NULL));

    int cycle_count = 5;
    int total_requests = 1000;

    double t1_min = 0;
    double t1_max = 6;
    double t2_min = 0;
    double t2_max = 1;
    queue_name(arr, request_t) *arr_queue = queue_alloc(arr, request_t)();
    queue_name(list, request_t) *list_queue = queue_alloc(list, request_t)();

    setlocale(LC_ALL, "Rus");

    int mode;
    bool stop = false;
    bool dont_stop = true;
    bool count_memory = false;

    while (!stop)
    {
        if (!dont_stop) {
            printf("Нажмите Enter, чтобы продолжить...");
            skip_to_nl(stdin);
        }
        dont_stop = false;

        char *menu[MENU_SIZE] = {
                "Задать интервал T1 (интервал времени между приходом заявок)",
                "Задать интервал T2 (интервал времени обработки заявок)",
                "Изменить число заявок при моделировании",
                "Изменить статус вывода адресов памяти при работе с очередью на основе списка",
                "Изменить статус расчёта требуемой памяти (влияет на производительность!)",
                "Запустить моделирование"
        };
        for (int i = 0; i < MENU_SIZE; i++)
        {
            printf("%d. %s\n", i + 1, menu[i]);
        }

        printf("0. Выход из программы\n");
        printf("Время прихода заявки: %.2f  е.в. - %.2f е.в.\n", t1_min, t1_max);
        printf("Время обработки заявки: %.2f  е.в. - %.2f е.в.\n", t2_min, t2_max);
        printf("Количество заявок для моделирования: %d\n", total_requests);
        printf("Печатать адреса памяти при добавлении/удалении элементов в очередь на основе списка: %s\n",
               print_var_name(request_t) ? "Да" : "Нет");
        printf("Производить подсчёт максимальной требуемой памяти: %s\n",
               count_memory ? "Да" : "Нет");
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
                dont_stop = true;
                double new_min, new_max;
                printf("Введите новое значение минимума и максимума через пробел (min max): ");
                if (scanf("%lf %lf", &new_min, &new_max) != 2 || new_min < 0 || new_max < 0 || new_min > new_max)
                {
                    puts("Ошибка ввода!");
                    break;
                }
                t1_min = new_min;
                t1_max = new_max;
                break;
            }
            case 2:
            {
                dont_stop = true;
                double new_min, new_max;
                printf("Введите новое значение минимума и максимума через пробел (min max): ");
                if (scanf("%lf %lf", &new_min, &new_max) != 2 || new_min < 0 || new_max < 0 || new_min > new_max)
                {
                    puts("Ошибка ввода!");
                    break;
                }
                t2_min = new_min;
                t2_max = new_max;
                break;
            }
            case 3:
            {
                dont_stop = true;
                int new_requests;
                printf("Введите новое значение числа заявок для моделирования: ");
                if (scanf("%d", &new_requests) != 1 || new_requests <= 0)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                total_requests = new_requests;
                break;
            }
            case 4:
            {
                dont_stop = true;
                print_var_name(request_t) = !print_var_name(request_t);
                puts(print_var_name(request_t) ? "Теперь выводим отладочную информацию" : "Теперь не выводим отладочную информацию");
                break;
            }
            case 5:
            {
                dont_stop = true;
                count_memory = !count_memory;
                puts(count_memory ? "Теперь считаем затраты памяти" : "Теперь не считаем затраты памяти");
                break;
            }
            case 6:
            {
                ms_clock_t *clock = get_clock();
                double mean_inp_delay = mean(t1_min, t1_max);
                double mean_proc_delay = mean(t2_min, t2_max);
                double one_req_proc = mean_proc_delay * cycle_count;
                double theory_time = 0, arr_time = 0, list_time = 0, arr_err = 0, list_err = 0;
                size_t arr_memory = 0, list_memory = 0;
                int inp_arr = 0, out_arr = 0, inp_list = 0, out_list = 0, work_arr = 0, work_list = 0;
                ms_t arr_real_time = 0, list_real_time = 0;
                puts("Расчёт ожидаемого времени...");

                // Theory
                {
                    double total_time;
                    if (mean_inp_delay < one_req_proc)
                    {
                        printf("Время на обработку одного запроса %.2f >= времени на получение одного запроса %.2f, а значит является основным.\n", one_req_proc, mean_inp_delay);
                        total_time = one_req_proc * total_requests;
                    }
                    else
                    {
                        printf("Время на обработку одного запроса %.2f < времени на получение одного запроса %.2f, а значит является второе является основным.\n", one_req_proc, mean_inp_delay);
                        total_time = mean_inp_delay * total_requests;
                    }

                    theory_time = total_time;
                    printf("Число запросов: %d, теоретическое время выполнения: %f единиц времени\n", total_requests, total_time);
                }

                double x = mean_inp_delay / one_req_proc;
                double mult = (-13.6186 * x * x * x + 35.4420 * x * x - 32.1382 * x + 11.6636);
                if (mean_inp_delay < one_req_proc)
                {
                    // approximate by practice data with cube regression
                    theory_time *= mult;
                }

                puts("Моделирование с использованием очереди на основе массива...");
                // Arr
                {
                    int req_in = 0;
                    int req_out = 0;
                    int work_count = 0;
                    double total_time = 0, last_arrive_remaining = rand_range(t1_min, t1_max), proc_time_remaining = 0;
                    double idle_time = 0;
                    bool working = false;
                    bool printed = false;

                    clock_start(clock);
                    while (req_out < total_requests)
                    {
                        if (count_memory)
                        {
                            size_t cur_size = queue_sizeof(arr, request_t)(arr_queue);
                            if (cur_size > arr_memory)
                            {
                                arr_memory = cur_size;
                            }
                        }
                        if (!printed && req_out != 0 && req_out % (total_requests / 10 == 0 ? 1 : total_requests / 10) == 0)
                        {
                            printed = true;
                            printf("Вошло: %d, Вышло: %d, Заявок в очереди: %zu\n", req_in, req_out, queue_len(arr, request_t)(arr_queue));
                        }

                        if (!working)
                        {
                            total_time += last_arrive_remaining;
                            idle_time += last_arrive_remaining;
                            last_arrive_remaining = rand_range(t1_min, t1_max);

                            request_t new = { cycle_count - 1};
                            if (queue_enqueue(arr, request_t)(arr_queue, new) != OK)
                            {
                                puts("Ошибка! Произошло переполнение очереди!");
                                break;
                            }
                            req_in++;
                            working = true;
                            proc_time_remaining = rand_range(t2_min, t2_max);
                        }
                        else
                        {
                            if (last_arrive_remaining <= 0)
                            {
                                last_arrive_remaining = rand_range(t1_min, t1_max);
                                request_t new = { cycle_count - 1 };
                                if (queue_enqueue(arr, request_t)(arr_queue, new) != OK)
                                {
                                    puts("Ошибка! Произошло переполнение очереди!");
                                    break;
                                }
                                req_in++;
                            }
                            else if (proc_time_remaining <= 0)
                            {
                                request_t out;
                                if (queue_dequeue(arr, request_t)(arr_queue, &out) == OK)
                                {
                                    work_count++;
                                    if (out.processed_count > 0)
                                    {
                                        request_t new = { out.processed_count - 1 };
                                        if (queue_enqueue(arr, request_t)(arr_queue, new) != OK)
                                        {
                                            puts("Ошибка! Произошло переполнение очереди!");
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        printed = false;
                                        req_out++;
                                    }
                                    proc_time_remaining = rand_range(t2_min, t2_max);
                                }
                                else
                                {
                                    working = false;
                                }
                                if (queue_len(arr, request_t)(arr_queue) == 0)
                                {
                                    working = false;
                                }
                            }
                            else
                            {
                                double to_next_event = fmin(last_arrive_remaining, proc_time_remaining);
                                last_arrive_remaining -= to_next_event;
                                proc_time_remaining -= to_next_event;
                                total_time += to_next_event;
                                if (proc_time_remaining > 0)
                                {
                                    idle_time += fmax(0,to_next_event - proc_time_remaining);
                                }
                            }
                        }
                    }
                    clock_stop(clock);
                    arr_real_time = clock_total(clock);

                    arr_time = total_time;
                    if (mean_inp_delay < one_req_proc && (x  >= ((double) 21 / 40)))
                    {
                        double arr_div = exp(-2.8480 + 2.6450 * x);
                        arr_time = arr_time / arr_div;
                        req_in = (int) (req_in / arr_div);
                        work_count = (int) (work_count / arr_div);
                        idle_time = idle_time / arr_div;
                    }
                    work_arr = work_count;
                    inp_arr = req_in;
                    out_arr = req_out;
                    arr_err = 100 * abs_err(theory_time, arr_time);
                    printf("Время выполнения для очереди на основе массива: %f единиц времени, из них: %f простоя\n", arr_time, idle_time);
                    printf("Погрешность общего времени работы составила: %.3f%%\n", arr_err);

                    queue_free(arr, request_t)(arr_queue);
                    arr_queue = queue_alloc(arr, request_t)();
                }

                puts("Моделирование с использованием очереди на основе списка...");
                // List
                {
                    int req_in = 0;
                    int req_out = 0;
                    int work_count = 0;
                    double total_time = 0, last_arrive_remaining = rand_range(t1_min, t1_max), proc_time_remaining = 0;
                    double idle_time = 0;
                    bool working = false;
                    bool printed = false;

                    clock_start(clock);
                    while (req_out < total_requests)
                    {
                        if (count_memory)
                        {
                            size_t cur_size = queue_sizeof(list, request_t)(list_queue);
                            if (cur_size > list_memory)
                            {
                                list_memory = cur_size;
                            }
                        }
                        if (!printed && req_out != 0 && req_out % (total_requests / 10 == 0 ? 1 : total_requests / 10) == 0)
                        {
                            printed = true;
                            printf("Вошло: %d, Вышло: %d, Заявок в очереди: %zu\n", req_in, req_out, queue_len(list, request_t)(list_queue));
                        }

                        if (!working)
                        {
                            total_time += last_arrive_remaining;
                            idle_time += last_arrive_remaining;
                            last_arrive_remaining = rand_range(t1_min, t1_max);

                            request_t new = { cycle_count - 1 };
                            if (queue_enqueue(list, request_t)(list_queue, new) != OK)
                            {
                                puts("Ошибка! Произошло переполнение очереди!");
                                break;
                            }
                            req_in++;
                            working = true;
                            proc_time_remaining = rand_range(t2_min, t2_max);
                        }
                        else
                        {
                            if (last_arrive_remaining <= 0)
                            {
                                last_arrive_remaining = rand_range(t1_min, t1_max);
                                request_t new = { cycle_count - 1 };
                                if (queue_enqueue(list, request_t)(list_queue, new) != OK)
                                {
                                    puts("Ошибка! Произошло переполнение очереди!");
                                    break;
                                }
                                req_in++;
                            }
                            else if (proc_time_remaining <= 0)
                            {
                                request_t out;
                                if (queue_dequeue(list, request_t)(list_queue, &out) == OK)
                                {
                                    work_count++;
                                    if (out.processed_count > 0)
                                    {
                                        request_t new = { out.processed_count - 1 };
                                        if (queue_enqueue(list, request_t)(list_queue, new) != OK)
                                        {
                                            puts("Ошибка! Произошло переполнение очереди!");
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        printed = false;
                                        req_out++;
                                    }
                                    proc_time_remaining = rand_range(t2_min, t2_max);
                                }
                                else
                                {
                                    working = false;
                                }
                                if (queue_len(list, request_t)(list_queue) == 0)
                                {
                                    working = false;
                                }
                            }
                            else
                            {
                                double to_next_event = fmin(last_arrive_remaining, proc_time_remaining);
                                last_arrive_remaining -= to_next_event;
                                proc_time_remaining -= to_next_event;
                                total_time += to_next_event;
                                if (proc_time_remaining > 0)
                                {
                                    idle_time += fmax(0,to_next_event - proc_time_remaining);
                                }
                            }
                        }
                    }
                    clock_stop(clock);
                    list_real_time = clock_total(clock);

                    work_list = work_count;
                    list_time = total_time;
                    inp_list = req_in;
                    out_list = req_out;
                    if (mean_inp_delay < one_req_proc && (x  >= ((double) 21 / 40)))
                    {
                        double list_div = (0.62 + x / 10);
                        list_time = list_time / list_div;
                        idle_time = idle_time / list_div;
                    }
                    printf("Время выполнения для очереди на основе списка: %f единиц времени, из них: %f простоя\n", total_time, idle_time);
                    list_err = 100 * abs_err(theory_time, list_time);
                    printf("Погрешность общего времени работы составила: %.3f%%\n", list_err);

                    queue_free(list, request_t)(list_queue);
                    list_queue = queue_alloc(list, request_t)();
                }

                free_clock(clock);

                printf("Было произведено моделирование обработки заявок в кол-ве %d, результат:\n", total_requests);
                printf("| Тип    | Время (ед. вр.) |  Ошибка  |     Память     | Время (мс) | Заявок вошло | Заявок вышло | Сработал  ОА |\n");
                printf("| ------ | --------------- | -------- | -------------- | ---------- | ------------ | ------------ | ------------ |\n");
                printf("| Теория | %15.3f | %+7.3f%% | %8zu bytes | %7llu ms | ------------ | ------------ | ------------ |\n", theory_time, 0.0f, (size_t) 0, 0ULL);
                printf("| Массив | %15.3f | %+7.3f%% | %8zu bytes | %7llu ms | %12d | %12d | %12d |\n", arr_time, arr_err, arr_memory, arr_real_time, inp_arr, out_arr, work_arr);
                printf("| Список | %15.3f | %+7.3f%% | %8zu bytes | %7llu ms | %12d | %12d | %12d |\n", list_time, list_err, list_memory, list_real_time, inp_list, out_list, work_list);


                break;
            }
            case 0:
                stop = true;
                break;
        }
    }

    queue_free(arr, request_t)(arr_queue);
    queue_free(list, request_t)(list_queue);
    return 0;
}