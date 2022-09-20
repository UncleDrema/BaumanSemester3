#!/bin/bash

test_script_dir="func_tests/scripts/"
test_script_name="func_tests.sh"
gcno_file="app-main.gcno"
gcda_file="app-main.gcda"
app_file="app.exe"

if [ ! -f $gcno_file ] || [ ! -f $app_file ]; then
    echo "Program was not properly compiled for coverage test! Please, use build_gcov.sh script before collecting coverage data"
    exit 1
fi

cd "$test_script_dir" || exit
./$test_script_name > /dev/null
cd ../../

if [ ! -f $gcda_file ]; then
    echo "No tests were launched or $gcda_file not found, test coverage: 0.00%"
else
    amount=$(gcov ./*.gcda | tac | grep -E "1?[0-9][0-9].[0-9][0-9]%" -m1 -o)
    echo "Test coverage: $amount"
fi

