#!/bin/bash
f1=$1
f2=$2

f1_text=$(cat "$f1")
f2_text=$(cat "$f2")

if [[ "$f1_text" == *"Result: "* ]]; then
    f1_out="${f1_text#*Result: }"
else
    f1_out=""
fi

if [[ "$f2_text" == *"Result: "* ]]; then
    f2_out="${f2_text#*Result: }"
else
    f2_out=""
fi

if [ "$f1_out" = "$f2_out" ]; then
    exit 0
fi
exit 1
