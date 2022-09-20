#!/bin/bash
run="run_all.sh"
build_d="build_debug.sh"
build_r="build_release.sh"
build_g="build_gcov.sh"
clean="clean.sh"
coverage="collect_coverage.sh"
check="check_scripts.sh"
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

all=("$build_d" "$build_r" "$build_g" "$clean" "$coverage" "$check" "$comparator" "$neg" "$pos" "$tests" "$run")

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
