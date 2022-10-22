#!/bin/bash
f1=$1
f2=$2

f1_text=$(cat "$f1")
f2_text=$(cat "$f2")

if [[ "$f1_text" == "$f2_text" && -n "$f1_text" && -n "$f2_text" ]]; then
    exit 0
fi
exit 1
