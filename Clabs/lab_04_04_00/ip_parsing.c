#include "ip_parsing.h"
#include "string_parsing.h"

int is_valid_ip(char *string)
{
    int result = NOT_VALID, temp;
    string = skip_blank(string);
    temp = starting_byte(string);
    if (temp != NOT_BYTE)
    {
        string = skip_char(skip_digits(string), '.');
        if (string)
        {
            temp = starting_byte(string);
            if (temp != NOT_BYTE)
            {
                string = skip_char(skip_digits(string), '.');
                if (string)
                {
                    temp = starting_byte(string);
                    if (temp != NOT_BYTE)
                    {
                        string = skip_char(skip_digits(string), '.');
                        if (string)
                        {
                            temp = starting_byte(string);
                            if (temp != NOT_BYTE)
                            {
                                string = skip_blank(skip_digits(string));
                                if (!*string)
                                    result = VALID;
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

int starting_byte(char *str)
{
    int result = NOT_BYTE, temp;
    if (*str)
    {
        temp = to_digit(*str);
        if (temp != NOT_DIGIT)
        {
            str++;
            if (*str)
            {
                result = temp * 10;
                temp = to_digit(*str);
                if (temp == NOT_DIGIT)
                    result = result / 10;
                else
                {
                    str++;
                    result += temp;
                    if (*str)
                    {
                        temp = to_digit(*str);
                        if (temp != NOT_DIGIT)
                        {
                            str++;
                            if (*str && to_digit(*str) != NOT_DIGIT)
                                result = NOT_BYTE;
                            else
                            {
                                result = result * 10 + temp;
                                if (result > BYTE_MAX)
                                    result = NOT_BYTE;
                            }
                        }
                    }
                }
            }
            else
                result = temp;
        }
    }

    return result;
}
