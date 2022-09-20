#!/bin/bash

build_r="build_release.sh"
build_g="build_gcov.sh"
clean="clean.sh"
coverage="collect_coverage.sh"
check="check_scripts.sh"
scripts_path="func_tests/scripts"
tests="func_tests.sh"

exit_message(){
    echo "$1"
    exit 1
}

# Компилируем программу
./"$build_r" || exit_message "---Build failed!---"

# Запускаем функциональные тесты
cd "$scripts_path" || exit_message "---Cannot find path to scripts!---"
./"$tests"

# Собираем инфорамцию о покрытии
cd "../.." || exit_message "---Cannot return to working directory!---"
./"$build_g" || exit_message "---Build for coverage test failed!---"
./"$coverage" || exit_message "---Coverege test failed!---"

# Проверяем скрипты
./"$check" || exit_message "---Script checkup failed!---"

# Очищаем мусор после работы
./"$clean" || exit_message "---Cleaning failed!---"
