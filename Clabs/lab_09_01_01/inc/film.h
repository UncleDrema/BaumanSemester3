//
// Created by archdrema on 10/28/22.
// Описание типа и операций над данными о фильмах

#ifndef __FILM_H
#define __FILM_H

#include <err.h>
#include <stdio.h>

/**
 * Структура для хранения записи информации о фильме
 */
typedef struct
{
    /**
     * Название фильма
     */
    char *title;
    /**
     * Имя режиссёра
     */
    char *name;
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
    YEAR = 2,
} field_type_t;

/**
 * Структура для хранения запроса поиска записи о фильме
 */
typedef union
{
    /**
     * Название фильма
     */
    char *title;
    /**
     * Имя режиссёра
     */
    char *name;
    /**
     * Год выхода фильма
     */
    int year;
} film_query_t;

/**
 * Функция, возвращающая тип поля по его строковому представлению
 * @param str in строковое представление типа поля
 * @param out out тип поля
 * @return код ошибки
 */
err_t get_field_type(char *str, field_type_t *out);

/**
 * Выводит информацию о фильме
 * @param f in поток вывода
 * @param film in выводимая информация о фильме
 */
void print_film(FILE *f, const film_t *film);

/**
 * Вводит информацию о фильме
 * @param f in поток ввода
 * @param film out переменная, в которую происходит запись
 * @warning для строк будет выделена динамическая память, так что стоит освободить их после использования функции.
 * При ошибках значение равно NULL
 * @return код ошибки
 */
err_t read_film(FILE *f, film_t *film);

/**
 * Освобождает память, выделенную под строки в структуре описания фильма
 * @param film in указатель на данные о фильме
 */
void free_film(film_t *film);

/**
 * Освобождает память, выделенную под динамический массив информации о фильмах
 * @param arr in массив
 * @param len длина
 */
void free_film_arr(film_t *arr, size_t len);

/**
 * Выводит информацию о массиве фильмов
 * @param f in поток вывода
 * @param arr in массив фильмов
 * @param len длина массива
 */
void print_film_arr(FILE *f, const film_t *arr, size_t len);

/**
 * Вводит информацию о нескольких фильмах из файла в массив, сортируя при вводе
 * @param f out поток ввода
 * @param arr out массив записей информации о фильмах
 * @param comparator in функция сравнения
 * @param res_len out количество введённых записей с информацией о фильмах
 */
err_t read_film_arr_sorted(FILE *f, film_t **arr, int (*comparator)(const film_t *, const film_t *), size_t *res_len);

/**
 * Сравнение фильмов по названию
 * @param a in первый фильм
 * @param b in второй фильм
 * @return результат сравнения
 */
int compare_film_title(const film_t *a, const film_t *b);

/**
 * Сравнение фильмов по автору
 * @param a in первый фильм
 * @param b in второй фильм
 * @return результат сравнения
 */
int compare_film_name(const film_t *a, const film_t *b);

/**
 * Сравнение фильмов по году выхода
 * @param a in первый фильм
 * @param b in второй фильм
 * @return результат сравнения
 */
int compare_film_year(const film_t *a, const film_t *b);

/**
 * Сравнение фильма с запросом поиска по названию
 * @param a in фильм
 * @param b in запрос поиска
 * @return результат сравнения
 */
int compare_film_query_title(const film_t *a, const film_query_t *b);

/**
 * Сравнение фильма с запросом поиска по автору
 * @param a in фильм
 * @param b in запрос поиска
 * @return результат сравнения
 */
int compare_film_query_name(const film_t *a, const film_query_t *b);

/**
 * Сравнение фильма с запросом поиска по году выхода
 * @param a in фильм
 * @param b in запрос поиска
 * @return результат сравнения
 */
int compare_film_query_year(const film_t *a, const film_query_t *b);


/**
 * Ищет фильм бинарным поиском внутри массива по запросу
 * @param arr in массив, по которому происходит поиск
 * @param len длина массива
 * @param query in запрос поиска
 * @param comparator in функция сравнения фильмов
 * @param res_film out указатель на найденный фильм
 * @return код ошибки
 */
err_t find_film_binary(film_t *arr, size_t len, film_query_t *query, int (*comparator)(const film_t *, const film_query_t*), film_t **res_film);

#endif
