#include "./brick_game/tetris/s21_tetris.h"
#include "./gui/cli/cli.h"

int main() {
  init_cli();
  WINDOW *controls = newwin(20, 25, 0, 0);
  WINDOW *game_field = newwin(20, 20, 0, 26);
  WINDOW *score_table = newwin(20, 20, 0, 47);
  while (!GetAction()) {
    PrintControls(controls);
    PrintField(game_field);
    PrintTable(score_table);
  }
  endwin();
  return 0;
}
