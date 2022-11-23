#!/bin/bash
eval gcc -std=c99 -O0 -Wfloat-equal -Wfloat-conversion -c ./*.c "$1"
eval gcc -O0 ./*.o -o app.exe -lm
