#!/bin/bash
f_in=$1
f_expect=$2
f_args=""

if [ $# -gt 2 ]; then
    f_args=$(cat "$3")
fi

if [[ -z "$USE_VALGRIND" ]]; then
    eval ../../app.exe "$f_args" < "$f_in" > out.temp
    res=$?
else
    eval valgrind --log-file="v.temp" ../../app.exe "$f_args" < "$f_in" > out.temp 2>/dev/null
    res=$?
fi

if [ "$res" -ne 0 ]; then
    exit 1
fi

eval ./comparator.sh out.temp "$f_expect"
res=$?

if [ "$res" -eq 0 ]; then
    exit 0
fi
exit 1
