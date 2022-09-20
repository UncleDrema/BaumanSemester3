#!/bin/bash
f1=$1
f2=$2
f1_text=$(tr '\n' ' ' < "$f1")
f2_text=$(tr '\n' ' ' < "$f2")

f1_out=$(echo "$f1_text" | eval grep -oE "\(-?\)[0-9]+\(.[0-9]+\)?")
f2_out=$(echo "$f2_text" | eval grep -oE "\(-?\)[0-9]+\(.[0-9]+\)?")

if [ "$f1_out" = "$f2_out" ]; then
    exit 0
fi
exit 1
