#!/bin/bash
f_in=$1
f_expect=$2
f_expect_file=$4
f_args=""
converter="converter.exe"

call_converter() {
./$converter -t -T int -o "$1" "$2" &>/dev/null
}

if [ $# -gt 2 ]; then
    f_args=$(cat "$3")
    file_arg=$(echo "$f_args" | grep -oE "[^ ]+$")
    if [[ "$file_arg" == *.txt ]] || [[ "$file_arg" == *.txt.backup ]]; then
        if [[ "$file_arg" == *.txt.backup ]]; then
            cp "$file_arg" "${file_arg::-7}"
            file_arg="${file_arg::-7}"
        fi
        # shellcheck disable=SC2001
        new_file=$(echo "$file_arg" | sed 's/\(.*\)txt/\1bin/')
        call_converter "$new_file" "$file_arg"
        f_args=$(echo "$f_args" | awk "{sub(\".{\"length(\$NF)\"}$\",\"$new_file\")}7")
    fi
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

./$converter -b -T int -o "$file_arg" "$new_file" &>/dev/null

eval ./comparator.sh out.temp "$f_expect"
res1=$?
eval ./comparator.sh "$file_arg" "$f_expect_file" "easy"
res2=$?

if [ "$res1" -eq 0 ] && [ "$res2" -eq 0 ]; then
    exit 0
fi
exit 1
