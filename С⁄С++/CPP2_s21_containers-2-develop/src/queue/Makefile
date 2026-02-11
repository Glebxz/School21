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

all: queue

test: test_queue.o
	$(CC) $(CCFLAGS) --coverage -o test_queue test_queue.o $(GTEST_LIB)
	./test_queue
	#make gcov_report
	#$(OPEN_REPORT) report/index.html

queue.o: queue.cpp
	$(CC) $(CCFLAGS) -c queue.cpp

queue: queue.o
	$(CC) $(CCFLAGS) -o queue queue.o

test_queue.o: tests/test_queue.cpp
	$(CC) $(CCFLAGS) --coverage -c tests/test_queue.cpp

valgrind:
	valgrind ./test_queue
	#valgrind ./test_queue 2>&1 | grep "ERROR SUMMARY" > valgrind.txt
	make clean

gcov_report:
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info

clean:
	rm -rf *.o queue test_queue *.gc* *.info report/ *.txt *.dot
