#!/bin/bash
eval gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -c ./*.c
eval gcc ./*.o -o app.exe -lm
