#!/bin/bash

data_path="func_tests/data"
gcno_file="app-main.gcno"
gcda_file="app-main.gcda"
app_file="app.exe"

if [ ! -f $gcno_file ] || [ ! -f $app_file ]; then
    echo "Program was not properly compiled for coverage test! Please, use build_gcov.sh script before collecting coverage data"
    exit 1
fi

pos_in_raw=$(find $data_path -name "pos_[0-9][0-9]_in.txt" | sort | tr '\n' ' ')
neg_in_raw=$(find $data_path -name "neg_[0-9][0-9]_in.txt" | sort | tr '\n' ' ')

IFS=' ' read -r -a pos_in <<< "$pos_in_raw"
IFS=' ' read -r -a neg_in <<< "$neg_in_raw"

# Прогоняем позитивные и негативные тесты
for i in "${!pos_in[@]}"; do
    ./"$app_file" < "${pos_in[i]}" &>/dev/null
done

for i in "${!neg_in[@]}"; do
    ./"$app_file" < "${neg_in[i]}" &>/dev/null
done

if [ ! -f $gcda_file ]; then
    echo "No tests were launched or $gcda_file not found, test coverage: 0.00%"
else
    amount=$(gcov app-main.gcda | grep -E "1?[0-9][0-9].[0-9][0-9]%" -m1 -o)
    echo "Test coverage: $amount"
fi

