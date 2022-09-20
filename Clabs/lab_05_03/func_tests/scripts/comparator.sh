#!/bin/bash
f1=$1
f2=$2
mode=$3

if [ -z "$mode" ]; then
    mode="strict"
fi

f1_out=$(cat "$f1")
f2_out=$(cat "$f2")

if [ "$mode" == "strict" ]; then
    if [[ "$f1_out" == "$f2_out" ]]; then
        exit 0
    fi
elif [ "$mode" == "easy" ]; then
    if [ -z "$f2_out" ] || [[ "$f1_out" == "$f2_out" ]]; then
        exit 0
    fi
else
    echo "Unknown mode!"
    exit 2
fi

exit 1
