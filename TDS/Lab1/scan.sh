echo "Clang scan-build:"
scan-build clang *.c | sed '/^scan-build/d'
echo "Cppcheck:"
cppcheck . | grep error
rm a.out
