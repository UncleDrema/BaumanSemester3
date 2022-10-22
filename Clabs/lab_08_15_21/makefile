SRC_DIR := src
UNIT_DIR := unit_tests
OUT_DIR := out
INC_DIR := inc
TEST_DIR := unit_tests
APP_EXE := app.exe
UNIT_EXE := unit_tests.exe
OBJS := $(OUT_DIR)/matrix.o $(OUT_DIR)/utils.o $(OUT_DIR)/matrix_io.o
CHECK_OBJS := $(OUT_DIR)/check_matrix.o $(OUT_DIR)/check_utils.o
FUNC_TESTS := func_tests.sh
SCRIPTS := func_tests/scripts
CHECK_SCRIPTS := check_scripts.sh
SCAN := scan.sh
ERR_H := $(INC_DIR)/err.h
UNIT_FLAGS := -lcheck
COLLECT := collect_coverage.sh
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I inc

$(APP_EXE) : $(OUT_DIR) $(OBJS) $(OUT_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJS) $(OUT_DIR)/main.o -o $@

$(UNIT_EXE): $(OUT_DIR) $(OBJS) $(CHECK_OBJS) $(OUT_DIR)/check_main.o
	$(CC) $(CFLAGS) $(OBJS) $(CHECK_OBJS) $(OUT_DIR)/check_main.o $(UNIT_FLAGS) -o $@

$(OUT_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/matrix.o: $(SRC_DIR)/matrix.c $(INC_DIR)/matrix.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/matrix_io.o: $(SRC_DIR)/matrix_io.c $(INC_DIR)/matrix_io.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/utils.o: $(SRC_DIR)/utils.c $(INC_DIR)/utils.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_matrix.o: $(UNIT_DIR)/check_matrix.c $(INC_DIR)/check_matrix.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< $(UNIT_FLAGS) -o $@

$(OUT_DIR)/check_utils.o: $(UNIT_DIR)/check_utils.c $(INC_DIR)/check_utils.h $(ERR_H)
	$(CC) $(CFLAGS) -c $< $(UNIT_FLAGS) -o $@

$(OUT_DIR)/check_main.o: $(UNIT_DIR)/check_main.c
	$(CC) $(CFLAGS) -c $< $(UNIT_FLAGS) -o $@

$(OUT_DIR):
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
	$(RM) $(OUT_DIR)/*.*
	$(RM) *.exe

all: scan unit func coverage clean

ifndef VERBOSE
.SILENT:
endif

.PHONY : clean func scan all unit gcov coverage bench