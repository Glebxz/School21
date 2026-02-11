#ifndef CLI_H
#define CLI_H

#include <ncurses.h>

#if defined(SNAKE)
#include "../../brick_game/snake/s21_snake.h"
#endif
#if defined(TETRIS)
#include "../../brick_game/tetris/api.h"
#endif

void init_cli();
void PrintControls(WINDOW *controls);
void PrintField(WINDOW *game_field);
void PrintTable(WINDOW *score_table);
int GetAction();

#endif
