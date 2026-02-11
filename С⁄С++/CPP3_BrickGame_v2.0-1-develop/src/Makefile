CC = g++ -Wall -Werror -Wextra -pedantic
TETRIS_FOLDER = ./brick_game/tetris/
SNAKE_FOLDER = ./brick_game/snake/
CLI_FOLDER = ./gui/cli/

OS = $(shell uname -s)
ifeq ($(OS),Linux)
CHECK_LIBS = -lcheck -lrt -lpthread -lm -lsubunit
else
CHECK_LIBS = -lcheck
endif

all: snake_desktop tetris_desktop snake_cli tetris_cli

snake_desktop:
	make -C ./gui/desktop_snake/
	make -C ./gui/desktop_snake/ clean
	mv ./gui/desktop_snake/desktop ./s21_snake_desktop.out

tetris_desktop:
	make -C ./gui/desktop_tetris/
	make -C ./gui/desktop_tetris/ clean
	mv ./gui/desktop_tetris/desktop_tetris ./s21_tetris_desktop.out

snake_cli: s21_snake.a cli_snake
	$(CC) -DSNAKE main.cpp cli.a s21_snake_lib.a -o s21_snake_cli.out -lncurses
	make clean

tetris_cli: s21_tetris.a cli_teris
	$(CC) -DTETRIS main.cpp cli.a s21_tetris.a -o s21_tetris_cli.out -lncurses
	make clean

s21_tetris.a:
	$(CC) -c $(TETRIS_FOLDER)s21_tetris.cpp $(TETRIS_FOLDER)make_and_get.cpp $(TETRIS_FOLDER)moving.cpp $(TETRIS_FOLDER)rotation.cpp $(TETRIS_FOLDER)attaching.cpp $(TETRIS_FOLDER)api.cpp
	ar r s21_tetris.a s21_tetris.o make_and_get.o moving.o rotation.o attaching.o api.o
	rm -f *.o

s21_snake.a:
	$(CC) -c $(SNAKE_FOLDER)s21_snake.cpp $(SNAKE_FOLDER)moving.cpp
	ar r s21_snake_lib.a s21_snake.o moving.o
	rm -f *.o

cli_snake:
	$(CC) -DSNAKE -c $(CLI_FOLDER)cli.cpp -lncurses
	ar r cli.a cli.o
	rm -f *.o

cli_teris:
	$(CC) -DTETRIS -c $(CLI_FOLDER)cli.cpp -lncurses
	ar r cli.a cli.o
	rm -f *.o

install: snake_desktop
	mkdir ./bin
	mv s21_snake_desktop.out ./bin/s21_snake_desktop.out
	make clean

uninstall:
	rm -rf ./bin

dvi:
	doxygen Doxyfile

dist: install
	mkdir ./SnakeByGurneyfr-2.0
	cp ./bin/s21_snake_desktop.out ./SnakeByGurneyfr-2.0
	make uninstall
	tar -cvf SnakeByGurneyfr-2.0.tar ./SnakeByGurneyfr-2.0/s21_snake_desktop.out
	rm -rf ./SnakeByGurneyfr-2.0

test:
	$(CC) -c $(SNAKE_FOLDER)s21_snake.cpp $(SNAKE_FOLDER)moving.cpp -g -O0 --coverage
	ar r s21_snake_lib.a s21_snake.o moving.o
	rm -f *.o
	$(CC) -g -O0 --coverage test_snake.cpp s21_snake_lib.a -o test.out -lgtest
	./test.out
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage

clean:
	rm -rf *.o *.a *.gcda *.gcno *.gcov *.info ./doxygen high_score.txt

clout:
	make clean
	rm -f *.out
	rm -f *.tar
	rm -rf ./SnakeByGurneyfr-1.0
	rm -rf ./coverage
	make uninstall

style:
	clang-format -i *.c *.h *.cpp $(TETRIS_FOLDER)*.c $(CLI_FOLDER)*.cpp $(TETRIS_FOLDER)*.h $(CLI_FOLDER)*.h $(SNAKE_FOLDER)*.cpp $(SNAKE_FOLDER)*.h