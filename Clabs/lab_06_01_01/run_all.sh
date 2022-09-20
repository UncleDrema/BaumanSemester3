#!/bin/bash

build_d="build_debug.sh"
build_g="build_gcov.sh"
clean="clean.sh"
coverage="collect_coverage.sh"
check="check_scripts.sh"
scan="scan.sh"
scripts_path="func_tests/scripts"
tests="func_tests.sh"

exit_message(){
    echo "$1"
    exit 1
}

# Компилируем программу
./"$build_d" || exit_message "---Build failed!---"

# Проверяем скрипты
./"$check" || exit_message "---Script checkup failed!---"

# Проверяем код статическими анализаторами
./"$scan" || exit_message "---Program scanning failed!---"

# Запускаем функциональные тесты
cd "$scripts_path" || exit_message "---Cannot find path to scripts!---"
./"$tests" || exit_message "---Tests failed!---"

# Собираем инфорамцию о покрытии
cd "../.." || exit_message "---Cannot return to working directory!---"
./"$build_g" || exit_message "---Build for coverage test failed!---"
./"$coverage" || exit_message "---Coverege test failed!---"

# Очищаем мусор после работы
./"$clean" || exit_message "---Cleaning failed!---"
