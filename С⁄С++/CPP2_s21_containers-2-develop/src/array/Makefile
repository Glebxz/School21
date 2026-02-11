CC = g++
CCFLAGS = -Wall -Wextra -Werror -std=c++17

GTEST_LIB = -lgtest -lgtest_main -lpthread

ifeq ($(shell uname), Darwin)
	CCFLAGS += -Wno-sign-compare
endif

ifeq ($(shell grep -i microsoft /proc/version),)
	OPEN_REPORT := open
else
	OPEN_REPORT := wslview
endif

all: array

test: test_array.o
	$(CC) $(CCFLAGS) --coverage -o test_array test_array.o $(GTEST_LIB)
	./test_array
	#make gcov_report
	#$(OPEN_REPORT) report/index.html

array.o: array.cpp
	$(CC) $(CCFLAGS) -c array.cpp

array: array.o
	$(CC) $(CCFLAGS) -o array array.o

test_array.o: tests/test_array.cpp
	$(CC) $(CCFLAGS) --coverage -c tests/test_array.cpp

valgrind:
	valgrind ./test_array
	#valgrind ./test_array 2>&1 | grep "ERROR SUMMARY" > valgrind.txt
	make clean

gcov_report:
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info

clean:
	rm -rf *.o array test_array *.gc* *.info report/ *.txt *.dot
