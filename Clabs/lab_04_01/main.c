#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include "mystring.h"
#define OK 0

int check_strpbrk(char *str1, char *str2);
int check_strspn(char *str1, char *str2);
int check_strcspn(char *str1, char *str2);
int check_strchr(char *str, char symbol);
int check_strrchr(char *str, char symbol);

int main(void)
{
    int failed_checks = 0;
    // Проверяем strpbrk (указатель на первое вхождение символа из строки 2 в строке 1)
    // Обычный тест
    failed_checks += !check_strpbrk("Hello, world", "dor");
    // Нет совпадений
    failed_checks += !check_strpbrk("Hello, world", "fkm");
    // Проверяем strspn (длина начального участка строки 1, содержащего только символы строки 2)
    // Обычный тест
    failed_checks += !check_strspn("AABAACB", "AC");
    // Все символы строки 1 входят в строку 2
    failed_checks += !check_strspn("AABAACB", "ACB");
    // Первый символ строки 1 не входит в строку 2
    failed_checks += !check_strspn("AABAACB", "CB");
    // Проверяем strcspn (длина начального участка строки 1, не содержащего символов из строки 2)
    // Обычный тест
    failed_checks += !check_strcspn("Something testful!", "tf!");
    // Строка 1 не содержит символов из строки 2
    failed_checks += !check_strcspn("Something testful!", "?#*a");
    // Строка 1 начинается с символа из строки 2
    failed_checks += !check_strcspn("Something testful!", "?#St*a");
    // Проверяем strchr (указатель на первое вхождение символа в строке)
    // Обычный тест
    failed_checks += !check_strchr("I love C language, C is best!", 'C');
    // Нет символа в строке
    failed_checks += !check_strchr("I love C language, C is best!", 'D');
    // Запрашиваем поиск заверщающего нулевого символа
    failed_checks += !check_strchr("I love C language, C is best!", '\0');
    // Проверяем strrchr (указатель на последнее вхождение символа в строке)
    // Обычный тест
    failed_checks += !check_strrchr("I love C language, C is best!", 'C');
    // Нет символа в строке
    failed_checks += !check_strrchr("I love C language, C is best!", 'D');
    // Запрашиваем поиск заверщающего нулевого символа
    failed_checks += !check_strrchr("I love C language, C is best!", '\0');

    printf("Failed checks: %d\n", failed_checks);
    return failed_checks;
}

int check_strpbrk(char *str1, char *str2)
{
    const char *res1 = strpbrk(str1, str2);
    const char *res2 = my_strpbrk(str1, str2);
    return res1 == res2;
}

int check_strspn(char *str1, char *str2)
{
    size_t res1 = strspn(str1, str2);
    size_t res2 = my_strspn(str1, str2);
    return res1 == res2;
}

int check_strcspn(char *str1, char *str2)
{
    size_t res1 = strcspn(str1, str2);
    size_t res2 = my_strcspn(str1, str2);
    return res1 == res2;
}

int check_strchr(char *str, char symbol)
{
    const char *res1 = strchr(str, symbol);
    const char *res2 = my_strchr(str, symbol);
    return res1 == res2;
}

int check_strrchr(char *str, char symbol)
{
    const char *res1 = strrchr(str, symbol);
    const char *res2 = my_strrchr(str, symbol);
    return res1 == res2;
}
