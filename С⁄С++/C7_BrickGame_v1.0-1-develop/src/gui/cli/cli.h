#ifndef CLI_TETRIS_H
#define CLI_TETRIS_H

#include <ncurses.h>

#include "../../brick_game/tetris/api.h"

void init_cli();
void PrintControls(WINDOW *controls);
void PrintField(WINDOW *game_field);
void PrintTable(WINDOW *score_table);
int GetAction();

#endif
