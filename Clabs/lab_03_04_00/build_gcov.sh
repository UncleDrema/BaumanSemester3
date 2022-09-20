#!/bin/bash
eval gcc -std=c99 -Wall -Wvla -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -lm --coverage -o app.exe main.c
