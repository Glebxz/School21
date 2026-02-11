CC = gcc -Wall -Werror -Wextra -pedantic -std=c11
TETRIS_FOLDER = ./brick_game/tetris/
CLI_FOLDER = ./gui/cli/

OS = $(shell uname -s)
ifeq ($(OS),Linux)
CHECK_LIBS = -lcheck -lrt -lpthread -lm -lsubunit
else
CHECK_LIBS = -lcheck
endif

all: install

install: s21_tetris.a cli.a
	$(CC) main.c cli.a s21_tetris.a -o tetris.out -lncurses
	mkdir ./bin
	mv tetris.out ./bin/tetris.out
	make clean

uninstall:
	rm -rf ./bin

clean:
	rm -rf *.o *.a *.gcda *.gcno *.gcov *.info ./doxygen high_score.txt

dvi:
	doxygen Doxyfile

dist: install
	mkdir ./TetrisByGurneyfr-1.0
	cp ./bin/tetris.out ./TetrisByGurneyfr-1.0
	make uninstall
	tar -cvf TetrisByGurneyfr-1.0.tar ./TetrisByGurneyfr-1.0/tetris.out
	rm -rf ./TetrisByGurneyfr-1.0


test: s21_tetris.a
	checkmk ./tests/tetris_test.check > ./tests/tetris_test.c
	$(CC) ./tests/tetris_test.c s21_tetris.a $(CHECK_LIBS) -o tetris_test.out
	rm -f ./tests/tetris_test.c
	make clean
	./tetris_test.out

gcov_report:
	checkmk clean_mode=1 ./tests/tetris_test.check > ./tests/tetris_test.c
	$(CC) -fprofile-arcs -ftest-coverage ./tests/tetris_test.c $(TETRIS_FOLDER)s21_tetris.c $(TETRIS_FOLDER)make_and_get.c $(TETRIS_FOLDER)moving.c $(TETRIS_FOLDER)rotation.c $(TETRIS_FOLDER)attaching.c $(TETRIS_FOLDER)api.c $(CHECK_LIBS) -o tetris_test_gcov.out
	./tetris_test_gcov.out
	lcov -d . -c -o log.info
	genhtml -o report log.info
	rm -f ./tests/tetris_test.c ./tetris_test_gcov.out
	make clean

s21_tetris.a:
	$(CC) -c $(TETRIS_FOLDER)s21_tetris.c $(TETRIS_FOLDER)make_and_get.c $(TETRIS_FOLDER)moving.c $(TETRIS_FOLDER)rotation.c $(TETRIS_FOLDER)attaching.c $(TETRIS_FOLDER)api.c
	ar r s21_tetris.a s21_tetris.o make_and_get.o moving.o rotation.o attaching.o api.o
	rm -f *.o

cli.a:
	$(CC) -c $(CLI_FOLDER)cli.c -lncurses
	ar r cli.a cli.o
	rm -f *.o

clout:
	make clean
	rm -f *.out
	rm -rf ./TetrisByGurneyfr-1.0
	rm -rf ./report
	make uninstall

style:
	clang-format -i *.c *.h $(TETRIS_FOLDER)*.c $(CLI_FOLDER)*.c $(TETRIS_FOLDER)*.h $(CLI_FOLDER)*.h