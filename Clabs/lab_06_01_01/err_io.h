//
// Created by archdrema on 9/11/22.
//

#ifndef __ERR_IO_H
#define __ERR_IO_H

#include "err.h"
#include <stdio.h>

/**
 * Открывает файл (в случае неудачи кидает ошибку OPEN_ERR)
 * @param file_name путь к файлу
 * @param mode режим открытия файла
 * @return указатель на файл
 */
FUNC(FILE*, err_fopen, const char *restrict file_name, const char *restrict mode);

/**
 * Закрывает файл (в случае неудачи кидает ошибку CLOSE_ERR)
 * @param filestream указатель на файл, который подлежит закрытию
 */
FUNC(void, err_fclose, FILE *filestream);

#endif
