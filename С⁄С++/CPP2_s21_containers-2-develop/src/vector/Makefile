CC = g++
FLAGS = -Werror -Wall -Wextra -std=c++17
CLANG_FILE = -style=file:../../materials/linters/.clang-format
STYLE_TARGETS = *.tpp *.h 
TEST_FILE = tests/s21_vector_test.cpp
SRC_FILE_NAME = s21_vector

ifeq ($(shell uname), Darwin)
	FLAGS += -Wno-sign-compare
	TEST_FLAGS = $(shell pkg-config --libs gtest) -lm
else
	TEST_FLAGS =-lgtest -pthread -lsubunit -lrt -lm
endif

all: clean test

test: 
	$(CC) $(TEST_FILE) $(FLAGS) $(TEST_FLAGS) --coverage -L. -o test_vector
	./test_vector
	#make gcov_report

gcov_report:
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info

style_check:
	clang-format $(CLANG_FILE) -n $(STYLE_TARGETS) 

style_make:
	clang-format $(CLANG_FILE) -i $(STYLE_TARGETS)

leak: clean test
	leaks -atExit -- ./tests

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info *.out test_vector
	rm -rf gcov_report/ report
