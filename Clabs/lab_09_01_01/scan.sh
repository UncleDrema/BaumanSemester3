#!/bin/bash
echo "Clang scan-build:"
scan-build clang src/*.c -I inc -o app.exe | sed '/^scan-build/d'
echo "Cppcheck:"
cppcheck src --inline-suppr --suppress=toomanyconfigs
