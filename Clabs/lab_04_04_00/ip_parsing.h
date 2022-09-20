#ifndef _IP_PARSING_H
#define _IP_PARSING_H

#define NOT_BYTE -1
#define BYTE_MAX 255
#define NOT_VALID 0
#define VALID 1

int is_valid_ip(char *string);

int starting_byte(char *str);

#endif
