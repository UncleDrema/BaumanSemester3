#!/bin/bash
f_in=$1
f_expect=$2
f_expect_file=$4
f_compare=$(cat "$5")
f_args=""
converter="converter.exe"

call_converter() {
./$converter -t -T Student -o "$1" "$2" &>/dev/null
}

if [ $# -gt 2 ]; then
    f_args=$(cat "$3")
    IFS=' ' read -r -a args_arr <<< "$f_args"
    new_args=""
    for i in "${!args_arr[@]}"; do
        arg=${args_arr[$i]}
        if [[ "$arg" == *.txt ]] || [[ "$arg" == *.txt.backup ]]; then
            if [[ "$arg" == *.txt.backup ]]; then
                cp "$arg" "${arg::-7}"
                arg="${arg::-7}"
            fi
            # shellcheck disable=SC2001
            new_file=$(echo "$arg" | sed 's/\(.*\)txt/\1bin/')
            call_converter "$new_file" "$arg"
            arg="$new_file"
        fi
        new_args="$new_args $arg"
    done
    f_args=${new_args:1}
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

if [ $# -gt 2 ]; then
    IFS=' ' read -r -a args_arr <<< "$f_args"
    for i in "${!args_arr[@]}"; do
        arg=${args_arr[$i]}
        if [[ "$arg" == *.bin ]]; then
            # shellcheck disable=SC2001
            new_file=$(echo "$arg" | sed 's/\(.*\)bin/\1txt/')
            ./$converter -b -T Student -o "$new_file" "$arg" &>/dev/null
            arg="$new_file"
        fi
    done
fi

eval ./comparator.sh out.temp "$f_expect"
res1=$?
eval ./comparator.sh "$f_compare" "$f_expect_file" "easy"
res2=$?

if [ "$res1" -eq 0 ] && [ "$res2" -eq 0 ]; then
    exit 0
fi
exit 1
