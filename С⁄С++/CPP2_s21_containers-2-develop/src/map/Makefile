CC = g++
CCFLAGS = -Wall -Wextra -Werror -std=c++17
RANGEFLAG = 

GTEST_LIB = -lgtest -lgtest_main -lpthread

ifeq ($(shell uname), Darwin)
	CCFLAGS += -Wno-sign-compare -Wno-unused-parameter
	RANGEFLAG += --filter range
endif

all: 
	make clean
	g++ -Wall -Werror -Wextra -std=c++20 main.cpp
	./a.out

style:
	clang-format -i *.cpp *.h *.tpp

test: test_set.o
	$(CC) $(CCFLAGS) --coverage -o test_map test_map.o $(GTEST_LIB)
	./test_map
	#make gcov_report
	#wslview report/index.html

test_set.o: tests/test_map.cpp
	$(CC) $(CCFLAGS) --coverage -c tests/test_map.cpp

gcov_report:
	lcov -t "test" -o test.info -c -d . $(RANGEFLAG)
	genhtml -o report test.info

clean:
	rm -rf *.o test_map *.gc* *.info report/ *.txt *.out *.png *.dot
