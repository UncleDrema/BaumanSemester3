#!/bin/bash
f_in=$1
f_expect=$2
f_args=""

if [ $# -gt 2 ]; then
    f_args=$(cat "$3")
fi

if [[ -z "$USE_VALGRIND" ]]; then
    cd ../.. || exit 1
    eval ./app.exe "$f_args" < "func_tests/scripts/$f_in" > out.temp
    res=$?
else
    cd ../.. || exit 1
    eval valgrind --log-file="v.temp" ./app.exe "$f_args" < "func_tests/scripts/$f_in" > out.temp 2>/dev/null
    res=$?
fi

if [ "$res" -ne 0 ]; then
    cd func_tests/scripts || exit 1
    exit 1
fi

eval ./func_tests/scripts/comparator.sh out.temp "func_tests/scripts/$f_expect"
res=$?
cd func_tests/scripts || exit 1

if [ "$res" -eq 0 ]; then
    exit 0
fi
exit 1
