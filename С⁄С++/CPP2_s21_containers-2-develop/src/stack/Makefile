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

all: stack

test: test_stack.o
	$(CC) $(CCFLAGS) --coverage -o test_stack test_stack.o -I$(GTEST_INCLUDE) -L$(GTEST_LIB_DIR) $(GTEST_LIB)
	./test_stack
	#make gcov_report
	#$(OPEN_REPORT) report/index.html

stack.o: stack.cpp
	$(CC) $(CCFLAGS) -c stack.cpp

stack: stack.o
	$(CC) $(CCFLAGS) -o stack stack.o

test_stack.o: tests/test_stack.cpp
	$(CC) $(CCFLAGS) --coverage -c tests/test_stack.cpp

valgrind:
	valgrind ./test_stack
	#valgrind --leak-check=full --track-origin=yes ./test_stack 2>&1 | grep "ERROR SUMMARY" > valgrind.txt

gcov_report:
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

clean:
	rm -rf *.o stack test_stack *.gc* *.info report/ *.txt *.dot
