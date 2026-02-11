CC = g++
CCFLAGS = -Wall -Wextra -Werror -std=c++17
GTEST_LIB = -lgtest -lgtest_main -lpthread
OPEN_REPORT := open

ifeq ($(shell uname), Darwin)
	CCFLAGS += -Wno-sign-compare
endif

all: main

main: main.o
	$(CC) $(CCFLAGS) -o main main.o

test: s21_list_test.o
	$(CC) $(CCFLAGS) --coverage -o test_list s21_list_test.o $(GTEST_LIB)
	./test_list
	#make gcov_report

main.o: main.cpp s21_list.h s21_list.tpp
	$(CC) $(CCFLAGS) -c main.cpp

s21_list_test.o: tests/s21_list_test.cpp s21_list.h s21_list.tpp
	$(CC) $(CCFLAGS) --coverage -c tests/s21_list_test.cpp

GCOV_FLAGS = -fprofile-arcs -ftest-coverage --coverage

#gcov_report: FLAGS += $(GCOV_FLAGS)
#
#gcov_report: test
#	
#	mkdir -p report
#	gcov -o report/report.html --exclude tests/test.c
#	#open report/report.html

gcov_report:
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info

clean:
	rm -rf *.o main test_list *.gc* *.info report/ *.txt *.dot
