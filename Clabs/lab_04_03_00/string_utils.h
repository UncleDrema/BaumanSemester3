#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

int split(char *string, char **words, char *delim);

int filter_words_remove(char **words, int w_count, char *remove_word, char **filtered_words);

char *remove_symbol_occures_skip_n(char *str, char symbol, int n);

#endif
