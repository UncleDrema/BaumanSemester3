// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by archdrema on 9/24/22.
//

#include "book.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#define GENRE_BUF_LEN 8
#define NULL_FPRINTF(f, ...) if (f != NULL) fprintf(f, __VA_ARGS__)

err_t read_book(FILE *f, book_t *book, FILE *prompt_output)
{
    // reading author
    NULL_FPRINTF(prompt_output, "Please, input author (str): ");
    if (fgets(book->author, AUTHOR_NAME_LEN, f) == NULL)
    {
        if (feof(f))
        {
            return NO_MORE_DATA;
        }
        else
        {
            return IO_ERROR;
        }
    }

    char *new_line;

    new_line = strchr(book->author, '\n');
    if (new_line != NULL)
    {
        *new_line = '\0';
    }
    else
    {
        skip_to_nl(f);
    }

    if (strlen(book->author) == 0)
    {
        return IO_ERROR;
    }

    // reading title
    NULL_FPRINTF(prompt_output, "Please, input title (str): ");
    if (fgets(book->title, TITLE_NAME_LEN, f) == NULL)
    {
        return IO_ERROR;
    }

    new_line = strchr(book->title, '\n');
    if (new_line != NULL)
    {
        *new_line = '\0';
    }
    else
    {
        skip_to_nl(f);
    }

    if (strlen(book->title) == 0)
    {
        return IO_ERROR;
    }

    // reading publisher
    NULL_FPRINTF(prompt_output, "Please, input publisher (str): ");
    if (fgets(book->publisher, PUBLISHER_NAME_LEN, f) == NULL)
    {
        return IO_ERROR;
    }

    new_line = strchr(book->publisher, '\n');
    if (new_line != NULL)
    {
        *new_line = '\0';
    }
    else
    {
        skip_to_nl(f);
    }

    if (strlen(book->publisher) == 0)
    {
        return IO_ERROR;
    }

    NULL_FPRINTF(prompt_output, "Please, input page count: ");
    if (fscanf(f, "%u", &book->page_count) != 1 || book->page_count == 0)
    {
        return IO_ERROR;
    }

    skip_to_nl(f);

    // reading genre
    NULL_FPRINTF(prompt_output, "Please, input genre (tech/fiction/child): ");
    char buf[GENRE_BUF_LEN];
    if (fgets(buf, GENRE_BUF_LEN, f) == NULL)
    {
        return IO_ERROR;
    }

    new_line = strchr(buf, '\n');
    if (new_line != NULL)
    {
        *new_line = '\0';
    }
    else
    {
        skip_to_nl(f);
    }

    if (strlen(buf) == 0)
    {
        return IO_ERROR;
    }

    book->genre = get_genre(buf);

    switch (book->genre)
    {
        case TECH:
            NULL_FPRINTF(prompt_output, "Please, input industry code: ");
            if (fscanf(f, "%d", &book->literature_kind.tech.industry) != 1 || book->literature_kind.tech.industry <= 0)
            {
                return IO_ERROR;
            }

            skip_to_nl(f);
            NULL_FPRINTF(prompt_output, "Please, input tech type (0 - national, 1 - translated): ");
            if (fscanf(f, "%d", &book->literature_kind.tech.type) != 1 || !is_valid_tech_type(book->literature_kind.tech.type))
            {
                return IO_ERROR;
            }

            skip_to_nl(f);
            NULL_FPRINTF(prompt_output, "Please, input publishment year: ");
            if (fscanf(f, "%hu", &book->literature_kind.tech.year) != 1)
            {
                return IO_ERROR;
            }

            skip_to_nl(f);
            break;
        case FICTION:
            NULL_FPRINTF(prompt_output, "Please, input fiction type (0 - novel, 1 - play, 2 - poem): ");
            if (fscanf(f, "%d", &book->literature_kind.fiction.type) != 1 || !is_valid_fiction_type(book->literature_kind.fiction.type))
            {
                return IO_ERROR;
            }

            skip_to_nl(f);
            break;
        case CHILD:
            NULL_FPRINTF(prompt_output, "Please, input child type (0 - fairy tale, 1 - child poem): ");
            if (fscanf(f, "%d", &book->literature_kind.child.type) != 1 || !is_valid_child_type(book->literature_kind.child.type))
            {
                return IO_ERROR;
            }

            skip_to_nl(f);
            break;
        default:
            return IO_ERROR;
    }

    return OK;
}

err_t read_books(FILE *f, book_t **arr, int *len)
{
    err_t rc = OK;
    int count;
    book_t temp;

    for (count = 0; rc == OK; count++)
    {
        rc = read_book(f, &temp, NULL);
    }
    count--;

    if (rc == NO_MORE_DATA)
    {
        rc = OK;
    }

    if (rc == OK)
    {
        *len = count;
        SAFE_FREE(*arr);
        *arr = calloc(count, sizeof(book_t));
        fseek(f, 0, SEEK_SET);

        for (int i = 0; i < count; ++i)
        {
            read_book(f, *arr + i, NULL);
        }
    }

    return rc;
}

void print_book(FILE *f, book_t *book, bool pretty)
{
    fprintf(f, pretty ? "Author: %s\n" : "%s\n", book->author);
    fprintf(f, pretty ? "Title: %s\n" : "%s\n", book->title);
    fprintf(f, pretty ? "Publisher: %s\n" : "%s\n", book->publisher);
    fprintf(f, pretty ? "Pages: %u\n" : "%u\n", book->page_count);
    print_genre(f, book->genre);
    switch (book->genre)
    {
        case TECH:
            fprintf(f, pretty ? "Industry: %d\n" : "%d\n", book->literature_kind.tech.industry);
            fprintf(f, pretty ? "(0 - national, 1 - translated): %d\n" : "%d\n", book->literature_kind.tech.type);
            fprintf(f, pretty ? "Year: %hu\n" : "%hu\n", book->literature_kind.tech.year);
            break;
        case FICTION:
            fprintf(f, pretty ? "(0 - novel, 1 - play, 2 - poem): %d\n" : "%d\n", book->literature_kind.fiction.type);
            break;
        case CHILD:
            fprintf(f, pretty ? "(0 - fairy tale, 1 - child poem): %d\n" : "%d\n", book->literature_kind.child.type);
            break;
        default:
            break;
    }
}

void print_books(FILE *f, int len, book_t *books, bool pretty)
{
    for (int i = 0; i < len; i++)
    {
        if (pretty)
        {
            fprintf(f, "[%d]:\n", i + 1);
        }
        print_book(f, books + i, pretty);
    }
}

genre_t get_genre(char *buf)
{
    if (strcmp(buf, "tech") == 0)
    {
        return TECH;
    }
    if (strcmp(buf, "fiction") == 0)
    {
        return FICTION;
    }
    if (strcmp(buf, "child") == 0)
    {
        return CHILD;
    }

    return NOT_A_GENRE;
}

void print_genre(FILE *f, genre_t genre)
{
    switch (genre)
    {
        case TECH:
            fputs("tech\n", f);
            break;
        case FICTION:
            fputs("fiction\n", f);
            break;
        case CHILD:
            fputs("child\n", f);
            break;
        default:
            fputs("UNKNOWN GENRE\n", f);
    }
}

bool is_valid_child_type(child_type_t type)
{
    return type == CHILD_POEM || type == FAIRY_TALE;
}

bool is_valid_tech_type(tech_type_t type)
{
    return type == TRANSLATED || type == NATIONAL;
}

bool is_valid_fiction_type(fiction_type_t type)
{
    return type == POEM || type == NOVEL || type == PLAY;
}

static char* authors[] = {"Billy", "Andrew", "Andy", "Clint", "Alexander", "Socratus", "M. L. Crass", "Marcus Avrelius"};

static char* publishers[] = {"EXMO", "Piastrus", "RZD", "FanZona", "Clickers", "BMSTU", "Samizdat"};

static char* titles_start[] = {"Good", "Bad", "Pretty", "Lovely", "Furious", "Optimized", "Unoptimized"};

static char* titles_end[] = {" Game", " War", " Life", " Dog", " Cat", " Girl", " Boy", " TDS"};

static industry_type industries[] = {DRINKS, TOBACCO, PHARMA, DURABLE_GOODS, CLOTHES_LUXURY, BANKS, FOOD, MEDIA, GAS_UTILITIES, ENTERTAINMENT, INTERACTIVE_MEDIA, SEMICONDUCTORS};

void gen_random_book(book_t *book)
{
    strncpy(book->author, RANDOM_ELEMENT(authors, STAT_ARR_SIZE(authors)), AUTHOR_NAME_LEN);
    book->author[AUTHOR_NAME_LEN - 1] = '\0';

    strncpy(book->publisher, RANDOM_ELEMENT(publishers, STAT_ARR_SIZE(publishers)), PUBLISHER_NAME_LEN);
    book->author[PUBLISHER_NAME_LEN - 1] = '\0';

    char buf[TITLE_NAME_LEN] = "";
    strcat(buf, RANDOM_ELEMENT(titles_start, STAT_ARR_SIZE(titles_start)));
    strcat(buf, RANDOM_ELEMENT(titles_end, STAT_ARR_SIZE(titles_end)));
    strcpy(book->title, buf);

    book->page_count = rand() % 1000 + 10;
    book->genre = rand() % 3 + 1;

    switch (book->genre)
    {
        case TECH:
            book->literature_kind.tech.type = rand() % 2;
            book->literature_kind.tech.year = rand() % 120 + 1900;
            book->literature_kind.tech.industry = RANDOM_ELEMENT(industries, STAT_ARR_SIZE(industries));
            break;
        case FICTION:
            book->literature_kind.fiction.type = rand() % 3;
        case CHILD:
            book->literature_kind.child.type = rand() % 2;
            break;
        default:
            break;
    }
}