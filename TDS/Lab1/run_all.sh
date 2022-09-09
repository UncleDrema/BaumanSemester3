#!/bin/bash

build_r="build_release.sh"
clean="clean.sh"
check="scan.sh"
scripts_path="func_tests/scripts"
tests="func_tests.sh"

exit_message(){
    echo "$1"
    exit 1
}

# Проверяем программу
./"$check" || exit_message "---Program checkup failed!---"

# Компилируем программу
./"$build_r" || exit_message "---Build failed!---"

# Запускаем функциональные тесты
cd "$scripts_path" || exit_message "---Cannot find path to scripts!---"
./"$tests"

# Собираем инфорамцию о покрытии
cd "../.." || exit_message "---Cannot return to working directory!---"

# Очищаем мусор после работы
./"$clean" || exit_message "---Cleaning failed!---"
