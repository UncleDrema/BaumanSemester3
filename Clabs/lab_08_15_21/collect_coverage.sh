#!/bin/bash

test_script_dir="func_tests/scripts/"
test_script_name="func_tests.sh"

cd "$test_script_dir" || exit
./$test_script_name > /dev/null
cd ../../

coverage=$(gcov out/*.gcda -n)
count=$(echo "$coverage" | grep -E "1?[0-9][0-9].[0-9][0-9]" -c)
code=$(echo "$coverage" | grep -E "1?[0-9][0-9].[0-9][0-9]" -o | tr '\n' '+')
code=${code::-1}
result=$(echo "scale=4; (${code::-1})/$count" | bc -l)
echo "Test coverage: $result%"