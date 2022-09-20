#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

int str_contains_sym(char *string, char symbol);

int count_str_in_str_arr(char **str_arr, int str_count, char *str);

int split(char *string, char **words, char *delims);

int get_unique_words(char **words, int w_count, char **uniques);

#endif
