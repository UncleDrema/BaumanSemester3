#!/bin/bash
eval gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -g -c main.c -o main.o
eval gcc main.o -o app.exe -lm
