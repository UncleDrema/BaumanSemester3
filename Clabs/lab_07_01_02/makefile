SRC_DIR := src
UNIT_DIR := unit_tests
OUT_DIR := out
INC_DIR := inc
TEST_DIR := unit_tests
BENCH_DIR := benchmark
APP_EXE := app.exe
UNIT_EXE := unit_tests.exe
BENCHMARK_EXE := benchmark.exe
RUN_BENCHMARK := run_benchmark.sh
OBJS := $(OUT_DIR)/sort.o $(OUT_DIR)/filter.o $(OUT_DIR)/comparators.o $(OUT_DIR)/io.o
CHECK_OBJS := $(OUT_DIR)/check_sort.o $(OUT_DIR)/check_filter.o $(OUT_DIR)/check_comparators.o
FUNC_TESTS := func_tests.sh
SCRIPTS := func_tests/scripts
CHECK_SCRIPTS := check_scripts.sh
SCAN := scan.sh
ERR_H := $(INC_DIR)/err.h
UNIT_FLAGS := -lcheck
COLLECT := collect_coverage.sh
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I inc

$(APP_EXE) : out $(OBJS) $(OUT_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJS) $(OUT_DIR)/main.o -o $@

$(UNIT_EXE): out $(OBJS) $(CHECK_OBJS) $(OUT_DIR)/check_main.o
	$(CC) $(CFLAGS) $(OBJS) $(CHECK_OBJS) $(OUT_DIR)/check_main.o $(UNIT_FLAGS) -o $@

$(BENCHMARK_EXE): out $(OUT_DIR)/benchmark.o $(OUT_DIR)/sort.o $(OUT_DIR)/comparators.o $(INC_DIR)/err.h
	$(CC) $(CFLAGS)  $(OUT_DIR)/benchmark.o $(OUT_DIR)/sort.o $(OUT_DIR)/comparators.o -o $@

$(OUT_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/sort.o: $(SRC_DIR)/sort.c $(INC_DIR)/sort.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/io.o : $(SRC_DIR)/io.c $(INC_DIR)/io.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/comparators.o : $(SRC_DIR)/comparators.c $(INC_DIR)/comparators.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/benchmark.o : $(BENCH_DIR)/benchmark.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/filter.o : $(SRC_DIR)/filter.c $(INC_DIR)/filter.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_sort.o: $(UNIT_DIR)/check_sort.c $(INC_DIR)/check_sort.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< $(UNIT_FLAGS) -o $@

$(OUT_DIR)/check_filter.o: $(UNIT_DIR)/check_filter.c $(INC_DIR)/check_filter.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< $(UNIT_FLAGS) -o $@

$(OUT_DIR)/check_comparators.o: $(UNIT_DIR)/check_comparators.c $(INC_DIR)/check_comparators.h
	$(CC) $(CFLAGS) -c $< $(UNIT_FLAGS) -o $@

$(OUT_DIR)/check_main.o: $(UNIT_DIR)/check_main.c
	$(CC) $(CFLAGS) -c $< $(UNIT_FLAGS) -o $@

bench: $(BENCHMARK_EXE)
	./$(RUN_BENCHMARK) > $(OUT_DIR)/benchmark.json

out:
	@mkdir -p $(OUT_DIR)

gcov: CFLAGS += --coverage
gcov: $(APP_EXE)

coverage:
	make gcov -B > /dev/null
	./$(COLLECT)

func: $(APP_EXE)
	cd $(SCRIPTS); ./$(FUNC_TESTS)

scan:
	./$(CHECK_SCRIPTS)
	./$(SCAN)

unit: $(UNIT_EXE)
	./$(UNIT_EXE)

clean:
	$(RM) -r $(OUT_DIR)
	$(RM) *.exe

all: scan unit func coverage clean

ifndef VERBOSE
.SILENT:
endif

.PHONY : clean func scan all unit gcov coverage bench out