#!/bin/bash
f_in=$1
f_args=""

if [ $# -gt 1 ]; then
    f_args=$(cat "$2")
fi

if [[ -z "$USE_VALGRIND" ]]; then
    eval ../../app.exe "$f_args" < "$f_in" > out.temp
    res=$?
else
    eval valgrind --log-file="v.temp" ../../app.exe "$f_args" < "$f_in" > out.temp 2>/dev/null
    res=$?
fi

if [ "$res" -eq 0 ]; then
    exit 0
else
    exit 1
fi
