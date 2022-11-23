#!/bin/bash
coverage="collect_coverage.sh"
check="check_scripts.sh"
scan="scan.sh"
run_benchmark="run_benchmark.sh"
scripts_path="func_tests/scripts"
comparator="$scripts_path/comparator.sh"
neg="$scripts_path/neg_case.sh"
pos="$scripts_path/pos_case.sh"
tests="$scripts_path/func_tests.sh"
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m'

all=("$coverage" "$check" "$comparator" "$neg" "$pos" "$tests" "$scan" "$run_benchmark")

check_script(){
    script=$1
    echo "Script: $script"
    res=$(shellcheck "$script")
    warnings=$(echo "$res" | grep -c "(warning)")
    errors=$(echo "$res" | grep -c "(error)")
    info=$(echo "$res" | grep -c "(info)")
    style=$(echo "$res" | grep -c "(style)")
    echo -e "${RED}Errors: $errors${NC} | ${ORANGE}Warnings: $warnings${NC} | ${GREEN}Info: $info${NC} | ${BLUE}Style: $style${NC}"
}

for el in "${all[@]}"; do
    check_script "$el"
done
