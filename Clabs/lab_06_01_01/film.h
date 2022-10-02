//
// Created by archdrema on 9/10/22.
//

#ifndef __FILM_H
#define __FILM_H
#define FILM_TITLE_LEN 25
#define FILM_NAME_LEN 25
#include "err.h"
#include <stdio.h>

/**
 * Структура для хранения записи информации о фильме
 */
typedef struct
{
    /**
     * Название фильма
     */
    char title[FILM_TITLE_LEN + 1];
    /**
     * Имя режиссёра
     */
    char name[FILM_NAME_LEN + 1];
    /**
     * Год выхода фильма
     */
    int year;
} film_t;

/**
 * Тип поля структуры film_t
 */
typedef enum
{
    TITLE = 0,
    NAME = 1,
    YEAR = 2
} field_type_t;

/**
 * Структура для хранения запроса поиска записи о фильме
 */
typedef union {
    /**
     * Название фильма
     */
    char title[FILM_TITLE_LEN + 1];
    /**
     * Имя режиссёра
     */
    char name[FILM_NAME_LEN + 1];
    /**
     * Год выхода фильма
     */
    int year;
} film_query_t;

/**
 * Функция, возвращающая тип поля по его строковому представлению (может кидать ошибку)
 * @param str строковое представление типа поля
 * @return тип поля
 */
FUNC(field_type_t, err_get_field_type, char *str);

/**
 * Выводит информацию о фильме
 * @param f поток вывода
 * @param film выводимая информация о фильме
 */
void print_film(FILE *f, film_t *film);

/**
 * Вводит информацию о фильме (может кидать ошибки INPUT_END/FILM_WRONG_FORMAT)
 * @param f поток ввода
 * @param film переменная, в которую происходит запись
 */
FUNC(void, err_read_film, FILE *f, film_t *film);

/**
 * Выводит информацию о массиве фильмов
 * @param f поток вывода
 * @param arr массив фильмов
 * @param len длина массива
 */
void print_film_arr(FILE *f, film_t *arr, int len);

/**
 * Вводит информацию о нескольких фильмах из файла в массив, сортируя при вводе (может кидать ошибки INPUT_END/TOO_MUCH_ENTRIES/FILM_WRONG_FORMAT)
 * @param f поток ввода
 * @param arr массив
 * @param maxLen максимальная длина массива
 * @param field_type тип поля, по которому сортируется массив
 * @return количество введённых записей с информацией о фильмах
 */
FUNC(int, err_read_film_arr_sorted, FILE *f, film_t *arr, int maxLen, int (*comparator)(film_t *, film_t *));

int compare_film_title(film_t *a, film_t *b);

int compare_film_name(film_t *a, film_t *b);

int compare_film_year(film_t *a, film_t *b);

int compare_film_query_title(film_t *a, film_query_t *b);

int compare_film_query_name(film_t *a, film_query_t *b);

int compare_film_query_year(film_t *a, film_query_t *b);


/**
 * Ищет фильм бинарным поиском внутри массива по запросу (может кидать ошибку NOT_FOUND, если не найдено)
 * @param arr массив, по которому происходит поиск
 * @param len длина массива
 * @param query запрос поиска
 * @return указатель на найденные фильм
 */
FUNC(film_t*, err_find_film_binary, film_t *arr, int len, film_query_t *query, int (*comparator)(film_t *, film_query_t *));

#endif
