echo "Clang scan-build:"
scan-build clang *.c -o app.exe | sed '/^scan-build/d'
echo "Cppcheck:"
cppcheck . --inline-suppr --suppress=toomanyconfigs
