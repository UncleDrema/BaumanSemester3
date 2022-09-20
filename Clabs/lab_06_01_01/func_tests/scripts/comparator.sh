#!/bin/bash
f1=$1
f2=$2

f1_out=$(cat "$f1")
f2_out=$(cat "$f2")

if [[ "$f1_out" == "$f2_out" && -n "$f1_out" && -n "$f2_out" ]]; then
    exit 0
fi
exit 1
