#!/bin/bash
f_in=$1
f_args=""

if [ $# -gt 1 ]; then
    f_args=$(cat "$2")
fi

if [[ -z "$USE_VALGRIND" ]]; then
    cd ../.. || exit 1
    eval ./app.exe "$f_args" < "func_tests/scripts/$f_in" > out/out.temp
    res=$?
else
    cd ../.. || exit 1
    eval valgrind --log-file="out/v.temp" --leak-check=full ./app.exe "$f_args" < "func_tests/scripts/$f_in" > out/out.temp 2>/dev/null
    res=$?
fi

cd func_tests/scripts || exit 1
if [ "$res" -eq 0 ]; then
    exit 0
else
    exit 1
fi
