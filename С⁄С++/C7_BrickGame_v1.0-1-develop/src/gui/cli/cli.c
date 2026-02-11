#include "cli.h"

void init_cli() {
  initscr();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  curs_set(0);
  has_colors();
  start_color();
  init_pair(0, COLOR_WHITE, COLOR_WHITE);
  init_pair(1, COLOR_BLACK, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLUE);
  init_pair(3, COLOR_GREEN, COLOR_GREEN);
  init_pair(4, COLOR_CYAN, COLOR_CYAN);
  init_pair(5, COLOR_RED, COLOR_RED);
  init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(7, COLOR_YELLOW, COLOR_YELLOW);
}

void PrintControls(WINDOW *controls) {
  mvwprintw(controls, 6, 0, "Strat: [s]");
  mvwprintw(controls, 7, 0, "Pause: [p]");
  mvwprintw(controls, 8, 0, "Terminate: [t]");
  mvwprintw(controls, 9, 0, "Moving: [arrow buttons]");
  mvwprintw(controls, 10, 0, "Action: [space]");
  wrefresh(controls);
}

void PrintField(WINDOW *game_field) {
  GameInfo_t game_info = updateCurrentState();
  chtype space = ' ' | A_STANDOUT;
  chtype open = '[' | A_STANDOUT;
  chtype close = ']' | A_STANDOUT;

  for (int i = 0; i < length; i++) {
    for (int k = 0, j = 0; j < width; j++, k++) {
      mvwaddch(game_field, i, k,
               game_info.field[i][j] > 0
                   ? open | COLOR_PAIR(game_info.field[i][j])
                   : space | COLOR_PAIR(game_info.field[i][j]));
      k++;
      mvwaddch(game_field, i, k,
               game_info.field[i][j] > 0
                   ? close | COLOR_PAIR(game_info.field[i][j])
                   : space | COLOR_PAIR(game_info.field[i][j]));
    }
  }
  wrefresh(game_field);
}

void PrintTable(WINDOW *score_table) {
  GameInfo_t game_info = updateCurrentState();
  chtype space = ' ' | A_STANDOUT;
  chtype open = '[' | A_STANDOUT;
  chtype close = ']' | A_STANDOUT;

  for (int i = 0; i < 4; i++) {
    for (int k = 0, j = 0; j < 4; j++, k++) {
      mvwaddch(score_table, i, k,
               game_info.next[i][j] > 0
                   ? open | COLOR_PAIR(game_info.next[i][j])
                   : space | COLOR_PAIR(game_info.next[i][j]));
      k++;
      mvwaddch(score_table, i, k,
               game_info.next[i][j] > 0
                   ? close | COLOR_PAIR(game_info.next[i][j])
                   : space | COLOR_PAIR(game_info.next[i][j]));
    }
  }
  mvwprintw(score_table, 6, 0, "Current score: %d", game_info.score);
  mvwprintw(score_table, 7, 0, "High score: %d", game_info.high_score);
  mvwprintw(score_table, 8, 0, "Level: %d", game_info.level);
  mvwprintw(score_table, 9, 0, "Speed: %d ms", game_info.speed);
  if (game_info.pause) {
    mvwprintw(score_table, 12, 0, ">PAUSE<");
  } else {
    mvwprintw(score_table, 12, 0, "       ");
  }
  wrefresh(score_table);
}

int GetAction() {
  int rtrn = 0;
  switch (getch()) {
    case 's':
      userInput(Start, 0);
      break;
    case 'p':
      userInput(Pause, 0);
      break;
    case 't':
      userInput(Terminate, 0);
      rtrn = 1;
      break;
    case KEY_LEFT:
      userInput(Left, 0);
      break;
    case KEY_RIGHT:
      userInput(Right, 0);
      break;
    case KEY_UP:
      userInput(Up, 0);
      break;
    case KEY_DOWN:
      userInput(Down, 0);
      break;
    case ' ':
      userInput(Action, 0);
      break;
    default:
      userInput(100, 0);
      break;
  }
  return rtrn;
}
