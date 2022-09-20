#ifndef _MYSTRING_H
#define _MYSTRING_H

const char *my_strpbrk(const char *s, const char *accept);

size_t my_strspn(const char *str, const char *accept);

size_t my_strcspn(const char *str, const char *reject);

const char *my_strchr(const char *s, int c_in);

const char *my_strrchr(const char *s, int c);

#endif
