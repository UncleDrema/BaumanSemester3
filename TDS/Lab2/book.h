// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/24/22.
//

#ifndef __BOOK_H
#define __BOOK_H
#include <stdbool.h>
#include <stdio.h>
#include "err.h"
#define AUTHOR_NAME_LEN 16
#define TITLE_NAME_LEN 32
#define PUBLISHER_NAME_LEN 16

/// Жанр книги
typedef enum
{
    /// Не жанр
    NOT_A_GENRE = 0,
    /// Техническая литература
    TECH = 1,
    /// Художественная литература
    FICTION = 2,
    /// Детская литература
    CHILD = 3
} genre_t;

/// Вид технической литературы
typedef enum
{
    /// Отечественная
    NATIONAL = 0,
    /// Переведённая
    TRANSLATED = 1
} tech_type_t;

/// Вид художественной литературы
typedef enum
{
    /// Роман
    NOVEL = 0,
    /// Пьеса
    PLAY = 1,
    /// Стихи
    POEM = 2
} fiction_type_t;

/// Вид детской литературы
typedef enum
{
    /// Сказка
    FAIRY_TALE = 0,
    /// Детские стихи
    CHILD_POEM = 1
} child_type_t;

/// Тип отрасли индустрии
typedef enum
{
    ENERGETICS = 101010,
    OIL_GAS = 101020,
    CHEMICALS = 151010,
    CONSTRUCTION_MATERIALS = 151020,
    CONTAINERS_PACKING = 151030,
    METAL_ORES = 151040,
    PAPER_FOREST = 151050,
    AEROSPACE = 201010,
    CONSTRUCTION = 201020,
    CONSTRUCTION_ENGINEERING = 201030,
    ELECTRIC_TOOLS = 201040,
    INDUSTRIAL_COMPLEXES = 201050,
    MACHINES = 201060,
    TADE_COMPANY_DISTRIBUTORS = 201070,
    COMMERCIAL_SERVICES = 202010,
    PROFESSIONAL_SERVICES = 202020,
    AVIATRANSPORT = 203010,
    AVIACOMPANY = 203020,
    SEA_TRANSPORT = 203030,
    AUTOMOBILE_RAILROAD = 203040,
    TRANSPORT_INFRASTRUCTURE = 203050,
    AUTOMOBILE_PARTS = 251010,
    AUTOMOBILES = 251020,
    DURABLE_GOODS = 252010,
    RECREATION_GOODS = 252020,
    CLOTHES_LUXURY = 252030,
    HOTELS_RESTAURANTS = 253010,
    CONSUMER_SERVICES = 253020,
    DISTRIBUTORS = 255010,
    INTERNET_MARKETING = 255020,
    RETAIL_TRADE = 255030,
    SPECIAL_RETAIL_TRADE = 255040,
    FOOD_RETAIL_TRADE = 301010,
    DRINKS = 302010,
    FOOD = 302020,
    TOBACCO = 302030,
    MEDICAL_EQUIPMENT = 351010,
    MEDICAL_SERVICES = 351020,
    MEDICAL_TECH = 351030,
    BIOTECH = 352010,
    PHARMA = 352020,
    SCIENCE_OF_LIFE = 352030,
    BANKS = 401010,
    MORTGAGE_FINANCE = 401020,
    FINANCE_SERVICES = 402010,
    CONSUMER_FINANCES = 402020,
    CAPITAL_MARKETS = 402030,
    INVESTMENT_MORTGAGE = 402040,
    INSURANCE = 403010,
    IT_SERVICES = 451020,
    PROGRAM_SUPPLY = 451030,
    COMMUNICATION_EQUIPMENT = 452010,
    TECH_DATA_STORAGE = 452020,
    ELECTRIC_EQUIPMENT = 452030,
    SEMICONDUCTORS = 453010,
    TELECOMMUNICATION_SERVICES = 501010,
    WIRELESS_TELECOMMUNICATION_SERVICES = 501020,
    MEDIA = 502010,
    ENTERTAINMENT = 502020,
    INTERACTIVE_MEDIA = 502030,
    ELECTRIC_UTILITIES = 551010,
    GAS_UTILITIES = 551020,
    DIVERSIFIED_UTILITIES = 551030,
    WATER_UTILITIES = 551040,
    RENEWABLE_ENERGY_SOURCES = 551050,
    REAL_ESTATE_INVESTMENT = 601010,
    REAL_ESTATE_MANAGEMENT = 601020
} industry_type;

/// Структура хранения информации о книге
typedef struct
{
    /// Фамилия автора
    char author[AUTHOR_NAME_LEN];
    /// Издательство
    char publisher[PUBLISHER_NAME_LEN];
    /// Название книги
    char title[TITLE_NAME_LEN];
    /// Количество страниц
    unsigned int page_count;
    /// Жанр книги
    genre_t genre;
    /// Специфичные для жанра данные
    union {
        /// Техническая литература
        struct {
            /// Отрасль хозяйства
            industry_type industry;
            /// Вид технической литературы
            tech_type_t type;
            /// Год издания
            unsigned short int year;
        } tech;
        /// Художественная литература
        struct
        {
            /// Вид художественной литературы
            fiction_type_t type;
        } fiction;
        /// Детская литература
        struct
        {
            // Вид детской литературы
            child_type_t type;
        } child;
    } literature_kind;
} book_t;

/// Структура для хранения ключей таблицы
typedef struct
{
    /// Индекс в базовой таблице
    unsigned int base_table_index;
    /// Число страниц
    unsigned int page_count;
} table_key_t;

/**
 * Прочитать книгу
 * @param f Поток ввода
 * @param book введённая книга
 * @param prompt_output поток вывода для приглашений ввода
 * @return код ошибки
 */
err_t read_book(FILE *f, book_t *book, FILE *prompt_output);

/**
 * Прочитать массив книг
 * @param f поток ввода
 * @param arr массив для ввода
 * @param len длина введённого массива
 * @return код ошибки
 */
err_t read_books(FILE *f, book_t **arr, int *len);

/**
 * Вывести книгу
 * @param f поток вывода
 * @param book выводимая книга
 * @param pretty красивый ли вывод
 */
void print_book(FILE *f, book_t *book, bool pretty);

/**
 * Вывести массив книг
 * @param f поток вывода
 * @param len длина массива
 * @param books массив книг
 * @param pretty красивый ли вывод
 */
void print_books(FILE *f, int len, book_t *books, bool pretty);

/**
 * Получить жанр по строке
 * @param buf строка, содержащая жанр
 * @return жанр литературы
 */
genre_t get_genre(char *buf);

void print_genre(FILE *f, genre_t);

bool is_valid_child_type(child_type_t type);

bool is_valid_tech_type(tech_type_t type);

bool is_valid_fiction_type(fiction_type_t type);

void gen_random_book(book_t *book);

#endif
