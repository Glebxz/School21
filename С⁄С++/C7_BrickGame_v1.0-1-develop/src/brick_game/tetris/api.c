#include "api.h"

#include "s21_tetris.h"

void userInput(UserAction_t action, bool hold) {
  FSM(action);
  hold = -hold;
}

GameInfo_t updateCurrentState() {
  GameInfo_t game_info = *GetGameInfo();
  return game_info;
}