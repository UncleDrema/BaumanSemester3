// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "sort.h"
#include <locale.h>
#include "book.h"
#include "utils.h"
#include "benchmark.h"
#define MENU_SIZE 13
#define STR_BUF 256

void gen_random_data(FILE *f, size_t count);

void recalculate_keys(table_key_t **keys, book_t *arr, int len);

void print_book_table_entry(book_t *book, int ind);

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    int mode;
    bool stop = false;
    bool dont_stop = true;

    book_t *arr = NULL;
    table_key_t *key_arr = NULL;
    bool key_formed = false;
    int len = 0;

    while (!stop)
    {
        if (!dont_stop)
        {
            printf("Нажмите Enter, чтобы продолжить...");
            skip_to_nl(stdin);
        }
        dont_stop = false;

        if (len == 0)
        {
            SAFE_FREE(arr);
        }

        char *menu[MENU_SIZE] = {
                "Создать файл, случайно заполненный данными",
                "Считать данные из файла в память",
                "Записать текущие данные в файл",
                "Вывести данные из памяти",
                "Добавить запись",
                "Удалить запись",
                "Провести замеры времени сортировки двумя способами",
                "Отсортировать таблицу",
                "Отсортировать таблицу ключей",
                "Вывести таблицу",
                "Вывести таблицу ключей",
                "Вывести таблицу по ключам",
                "Вывести отечественную тех. литературу по указанной отрасли указанного года"
        };
        for (int i = 0; i < MENU_SIZE; ++i)
        {
            printf("%d. %s\n", i + 1, menu[i]);
        }

        printf("0. Выход из программы\n");
        printf("Данные %s, длина: %d\n", arr == NULL ? "отсутствуют" : "присутствуют", len);
        printf("Выберите пункт меню: ");
        if (scanf("%d", &mode) != 1 || mode < 0 || mode > MENU_SIZE)
        {
            skip_to_nl(stdin);
            continue;
        }
        skip_to_nl(stdin);

        switch (mode) {
            case 1: {
                dont_stop = true;
                char buf[STR_BUF];
                printf("Введите путь к создаваемому файлу: ");
                if (fgets(buf, STR_BUF, stdin) == 0) {
                    printf("Ошибка ввода пути к файлу\n");
                    break;
                }
                remove_nl(buf);

                FILE *f = fopen(buf, "w");
                if (f == NULL) {
                    printf("Ошибка открытия файла\n");
                    break;
                }

                size_t amount;
                printf("Введите число записей для генерации: ");
                if (scanf("%zu", &amount) != 1 || amount == 0) {
                    printf("Некорректный ввод\n");
                    fclose(f);
                    break;
                }

                gen_random_data(f, amount);

                fclose(f);
                f = fopen(buf, "r");

                err_t rc = read_books(f, &arr, &len);

                if (rc == OK) {
                    puts("Файл заполнен данными и считан в память!");
                } else {
                    puts("Ошибка считывания данных!");
                }

                fclose(f);
                break;
            }
            case 2: {
                dont_stop = true;
                char buf[STR_BUF];
                printf("Введите путь к читаемому файлу: ");
                if (fgets(buf, STR_BUF, stdin) == 0) {
                    printf("Ошибка ввода пути к файлу\n");
                    break;
                }
                remove_nl(buf);

                FILE *f = fopen(buf, "r");
                if (f == NULL) {
                    printf("Ошибка открытия файла\n");
                    break;
                }

                err_t rc = read_books(f, &arr, &len);

                if (rc == OK) {
                    puts("Файл считан в память!");
                } else {
                    puts("Ошибка считывания данных!");
                }
                key_formed = false;

                fclose(f);
                break;
            }
            case 3:
            {
                dont_stop = true;
                char buf[STR_BUF];
                printf("Введите путь к файлу для записи: ");
                if (fgets(buf, STR_BUF, stdin) == 0) {
                    printf("Ошибка ввода пути к файлу\n");
                    break;
                }
                remove_nl(buf);

                FILE *f = fopen(buf, "w");
                if (f == NULL) {
                    printf("Ошибка открытия файла\n");
                    break;
                }

                print_books(f, len, arr, false);

                fclose(f);
                break;
            }
            case 4:
            {
                if (len <= 0)
                {
                    puts("Нет данных!");
                    break;
                }
                print_books(stdout, len, arr, true);
                break;
            }
            case 5:
            {
                dont_stop = true;
                book_t book;
                err_t rc = read_book(stdin, &book, stdout);

                if (rc != OK)
                {
                    puts("Ошибка ввода!");
                    break;
                }

                book_t *new = realloc(arr, (len + 1) * sizeof(book_t));
                if (new == NULL)
                {
                    puts("Ошибка выделения памяти!");
                    break;
                }

                arr = new;
                arr[len] = book;
                len++;
                key_formed = false;
                break;
            }
            case 6:
            {
                dont_stop = true;
                if (len <= 0)
                {
                    puts("Нет данных!");
                    break;
                }
                int index;

                printf("Введите номер записи для удаления: ");
                if (scanf("%d", &index) != 1 || index <= 0 || index > len)
                {
                    puts("Ошибка ввода!");
                    break;
                }
                skip_to_nl(stdin);
                index--;
                void *deleting = at_index(arr, index, sizeof(book_t));
                void *last = at_index(arr, len - 1, sizeof(book_t));

                memcpy(deleting, last, sizeof(book_t));

                book_t *new = realloc(arr, (len - 1) * sizeof(book_t));
                len--;
                if (new == NULL && len != 0)
                {
                    puts("Ошибка обрезки массива!");
                    break;
                }

                puts("Элемент удалён!");
                arr = new;
                key_formed = false;
                break;
            }
            case 7:
            {
                if (len <= 0)
                {
                    puts("Нет данных!");
                    break;
                }
                benchmark(arr, len);
                break;
            }
            case 8:
            {
                dont_stop = true;
                if (len <= 0)
                {
                    puts("Нет данных!");
                    break;
                }
                qsort(arr, len, sizeof(book_t), book_cmp);
                puts("Таблица отсортирована!");
                key_formed = false;
                // sort table
                break;
            }
            case 9:
            {
                dont_stop = true;
                if (len <= 0)
                {
                    puts("Нет данных!");
                    break;
                }

                if (!key_formed)
                {
                    puts("Таблица ключей пересчитана!");
                    recalculate_keys(&key_arr, arr, len);
                    key_formed = true;
                }

                qsort(key_arr, len, sizeof(table_key_t), key_cmp);
                puts("Таблица ключей отсортирована!");
                // sort key table
                break;
            }
            case 10:
            {
                if (len <= 0)
                {
                    puts("Нет данных!");
                    break;
                }

                puts("-----------------------------------------------------------------------------------------------------------------------------------------");
                printf("|%4s|%16s|%16s|%32s|%6s|%7s|%8s|%10s|%6s|%10s|%10s|\n", "Ind", "Author", "Publisher", "Title", "Pages", "Genre", "Industry", "Tech type", "Year", "Fict type", "Child type");
                puts("-----------------------------------------------------------------------------------------------------------------------------------------");
                for (int i = 0; i < len; ++i) {
                    print_book_table_entry(arr + i, i);
                }
                puts("-----------------------------------------------------------------------------------------------------------------------------------------");
                // print table
                break;
            }
            case 11:
            {
                if (len <= 0)
                {
                    puts("Нет данных!");
                    break;
                }
                if (!key_formed)
                {
                    puts("Таблица ключей пересчитана!");
                    recalculate_keys(&key_arr, arr, len);
                    key_formed = true;
                }

                puts("---------------------");
                printf("|%4s|%8s|%4s|\n", "Ind", "Base Ind", "Pages");
                puts("---------------------");
                table_key_t temp;
                for (int i = 0; i < len; ++i) {
                    temp = key_arr[i];
                    printf("|%4d|%8u|%5u|\n", i, temp.base_table_index, temp.page_count);
                }

                // print key table
                break;
            }
            case 12:
            {
                if (len <= 0)
                {
                    puts("Нет данных!");
                    break;
                }

                if (!key_formed)
                {
                    puts("Таблица ключей пересчитана!");
                    recalculate_keys(&key_arr, arr, len);
                    key_formed = true;
                }

                puts("-----------------------------------------------------------------------------------------------------------------------------------------");
                printf("|%4s|%16s|%16s|%32s|%6s|%7s|%8s|%10s|%6s|%10s|%10s|\n", "Ind", "Author", "Publisher", "Title", "Pages", "Genre", "Industry", "Tech type", "Year", "Fict type", "Child type");
                puts("-----------------------------------------------------------------------------------------------------------------------------------------");
                for (int i = 0; i < len; ++i) {
                    int ind = (int)key_arr[i].base_table_index;
                    print_book_table_entry(arr + ind, ind);
                }
                puts("-----------------------------------------------------------------------------------------------------------------------------------------");

                // print table by keys
                break;
            }
            case 13:
            {
                if (len <= 0)
                {
                    puts("Нет данных!");
                    break;
                }

                industry_type industry;
                unsigned short year;
                // print by query
                printf("Please, input industry code: ");
                if (scanf("%d", &industry) != 1)
                {
                    puts("Ошибка ввода!");
                }

                printf("Please, input publishment year: ");
                if (scanf("%hu", &year) != 1)
                {
                    puts("Ошибка ввода!");
                }

                puts("Подходящие записи в таблице:");
                int count = 0;
                puts("-----------------------------------------------------------------------------------------------------------------------------------------");
                printf("|%4s|%16s|%16s|%32s|%6s|%7s|%8s|%10s|%6s|%10s|%10s|\n", "Ind", "Author", "Publisher", "Title", "Pages", "Genre", "Industry", "Tech type", "Year", "Fict type", "Child type");
                puts("-----------------------------------------------------------------------------------------------------------------------------------------");
                book_t temp;
                for (int i = 0; i < len; ++i) {
                    temp = arr[i];
                    if (temp.literature_kind.tech.industry == industry && temp.literature_kind.tech.year == year)
                    {
                        print_book_table_entry(arr + i, count++);
                    }
                }
                if (count == 0)
                {
                    puts("Не найдено!");
                }
                puts("-----------------------------------------------------------------------------------------------------------------------------------------");

                break;
            }
            case 0:
                stop = true;
                break;
        }
    }

    SAFE_FREE(arr);

    return 0;
}

void recalculate_keys(table_key_t **keys, book_t *arr, int len)
{
    SAFE_FREE(*keys);

    table_key_t *new = calloc(len, sizeof(table_key_t));
    *keys = new;

    table_key_t temp = {0, 0};
    for (int i = 0; i < len; ++i)
    {
        temp.base_table_index = i;
        temp.page_count = arr[i].page_count;
        new[i] = temp;
    }
}

void gen_random_data(FILE *f, size_t count)
{
    book_t book;

    for (size_t i = 0; i < count; i++)
    {
        gen_random_book(&book);
        print_book(f, &book, false);
    }
}

void print_book_table_entry(book_t *book, int ind)
{
    char *genre, *tech_type = "", *fiction_type = "", *child_type = "";
    char industry[STR_BUF] = "";
    char year[STR_BUF] = "";
    switch (book->genre) {
        case TECH:
            genre = "tech";
            snprintf(industry, sizeof(industry), "%d", book->literature_kind.tech.industry);
            snprintf(year, sizeof(year), "%u", book->literature_kind.tech.year);
            switch (book->literature_kind.tech.type) {
                case NATIONAL:
                    tech_type = "national";
                    break;
                case TRANSLATED:
                    tech_type = "translated";
                    break;
            }
            break;
        case FICTION:
            genre = "fiction";
            switch (book->literature_kind.fiction.type) {
                case NOVEL:
                    fiction_type = "novel";
                    break;
                case PLAY:
                    fiction_type = "play";
                    break;
                case POEM:
                    fiction_type = "poem";
                    break;
            }
            break;
        case CHILD:
            genre = "child";
            switch (book->literature_kind.child.type) {
                case FAIRY_TALE:
                    child_type = "fairy tale";
                    break;
                case CHILD_POEM:
                    child_type = "child poem";
                    break;
            }
            break;
        default:
            genre = "UNKNOWN";
            break;
    }



    printf("|%4d|%16s|%16s|%32s|%6u|%7s|%8s|%10s|%6s|%10s|%10s|\n", ind, book->author, book->publisher, book->title, book->page_count, genre, industry, tech_type, year, fiction_type, child_type);
}