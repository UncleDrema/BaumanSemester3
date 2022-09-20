#ifndef _STRING_PARSING_H
#define _STRING_PARSING_H

#define NOT_DIGIT -1

int to_digit(char c);

char *skip_blank(char *str);

char *skip_char(char *str, char c);

char *skip_digits(char *str);

#endif
