//
// Created by archdrema on 9/10/22.
//

#ifndef __ERR_H
#define __ERR_H
#include <stdio.h>

/**
 * Название переменной, хранящей ошибку
 */
#define __STATE_NAME state
/**
 * Кидает ошибку и производит выход из функции
 */
#define THROWN(err) *__STATE_NAME = err; return
/**
 * Кидает ошибку и производит выход из функции, возвращая переданные аргменты
 */
#define THROW(err, ...) *__STATE_NAME = err; return __VA_ARGS__
/**
 * Ловит заданную ошибку и выполняет действия в блоке
 */
#define CATCH_ONLY(err, ...) if (*__STATE_NAME == err) {__VA_ARGS__}
/**
 * Ловит любую ошибку и выполняет действия в блоке
 */
#define CATCH(...) if (*__STATE_NAME != OK) {__VA_ARGS__}

/**
 * Объявление функции, кидающей ошибки, не принимающей аргументы
 */
#define FUNC_NOARGS(ret, name) ret name(int *__STATE_NAME)
/**
 * Объявление функции, кидающей ошибки, принимающей аргументы
 */
#define FUNC(ret, name, ...) ret name(__VA_ARGS__, int *__STATE_NAME)
#ifdef DEBUG
/**
 * Объявление функции main без аргументов
 */
#define MAIN_NOARGS FUNC_NOARGS(void, mainFunc); \
int main()                                      \
{                                               \
    err_t __STATE_NAME = OK;                    \
    mainFunc(&__STATE_NAME);                    \
    if (state != OK)                            \
    {                                           \
        printf("Got an exception: ");           \
        print_err(__STATE_NAME);                \
        puts("");                               \
    }                                           \
    return __STATE_NAME;                        \
}                                               \
FUNC_NOARGS(void, mainFunc)
/**
 * Объявление функции main с аргументами
 */
#define MAIN_ARGS(...) FUNC(void, mainFunc, __VA_ARGS__); \
int main(int argc, char **argv)                 \
{                                               \
    err_t __STATE_NAME = OK;                    \
    mainFunc(argc, argv, &__STATE_NAME);        \
    if (state != OK)                            \
    {                                           \
        printf("Got an exception: ");           \
        print_err(__STATE_NAME);                \
        puts("");                               \
    }                                           \
    return __STATE_NAME;                        \
}                                               \
FUNC(void, mainFunc, __VA_ARGS__)
#else
/**
 * Объявление функции main без аргументов
 */
#define MAIN_NOARGS FUNC_NOARGS(void, mainFunc); \
int main()                                      \
{                                               \
    err_t __STATE_NAME = OK;                    \
    mainFunc(&__STATE_NAME);                    \
    return __STATE_NAME;                        \
}                                               \
FUNC_NOARGS(void, mainFunc)

/**
 * Объявление функции main с аргументами
 */
#define MAIN_ARGS(...) FUNC(void, mainFunc, __VA_ARGS__); \
int main(int argc, char **argv)                 \
{                                               \
    err_t __STATE_NAME = OK;                    \
    mainFunc(argc, argv, &__STATE_NAME);        \
    return __STATE_NAME;                        \
}                                               \
FUNC(void, mainFunc, __VA_ARGS__)
#endif

/**
 * Прокидывает дальше по стеку вызовов заданную ошибку и возвращает заданное значение
 */
#define RETHROW_ONLY(err, elseRet) CATCH_ONLY(err, return elseRet;)
/**
 * Прокидывает дальше по стеку вызовов заданную ошибку
 */
#define RETHROWN_ONLY(err) CATCH_ONLY(err, return;)
/**
 * Прокидывает дальше по стеку вызовов любую ошибку и возвращает заданное значение
 */
#define RETHROW(elseRet) CATCH(return elseRet;)
/**
 * Прокидывает дальше по стеку вызовов любую ошибку
 */
#define RETHROWN CATCH(return;)

/**
 * Игнорирует ошибку
 */
#define IGNORE *__STATE_NAME = OK

/**
 * Вызов функции без аргументов
 */
#define CALL_NOARGS(fName) fName(__STATE_NAME);
/**
 * Вызов функции с аргументами
 */
#define CALL(fName, ...) fName(__VA_ARGS__, __STATE_NAME);

/**
 * Тип ошибки
 */
typedef int err_t;

/**
 * Отсутствие ошибки
 */
typedef enum
{
    OK = 0
} no_err_t;

/**
 * Ошибки ввода/вывода
 */
typedef enum
{
    OPEN_ERR = 1,
    CLOSE_ERR = 2
} io_err_t;

/**
 * Ошибки аргументов командной строки
 */
typedef enum
{
    NOT_ENOUGH_ARGS = 3,
    TOO_MUCH_ARGS = 4,
} args_err_t;

/**
 * Ошибки утилитарных функций
 */
typedef enum
{
    NOT_A_NUMBER = 5
} utils_err_t;

/**
 * Ошибки, связанные с работой программы по задаче
 */
typedef enum
{
    WRONG_FIELD = 6,
    FILM_WRONG_FORMAT = 7,
    INPUT_END = 8,
    NOT_FOUND = 9,
    TOO_MUCH_ENTRIES = 10
} task_err_t;

#ifdef DEBUG
/**
 * Печатает ошибку
 * @param err печатаемая ошибка
 */
void print_err(err_t err);
#endif

#endif
