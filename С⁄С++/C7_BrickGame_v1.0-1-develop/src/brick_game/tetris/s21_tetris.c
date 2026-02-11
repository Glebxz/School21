#include "s21_tetris.h"

void FSM(UserAction_t action) {
  static GameState_t game_state = GameInitialization;
  if (game_state == GameInitialization) {
    srand(time(NULL));
    MakeGameInfo();
  }
  if (action == Terminate) {
    FreeMemory();
    game_state = GameTerminate;
  }
  GameInfo_t *game_info = GetGameInfo();
  if (action == Pause) {
    game_info->pause = game_info->pause == 0 ? 1 : 0;
  }
  if (game_info->pause != 1) {
    switch (game_state) {
      case GameInitialization:
        game_state = GameStart;
        break;
      case GameStart:
        game_state = action == Start ? Spawn : GameStart;
        break;
      case Spawn:
        SpawnReset();
        game_state = CheckCollision() == 0 ? Moving : GameOver;
        break;
      case Moving:
        Move(action);
        game_state = Timer() == 1 ? Shifting : Moving;
        break;
      case Shifting:
        RemoveFigureFromField();
        game_state = MoveDown() == 0 ? Moving : Attaching;
        PutFigureOnField();
        break;
      case Attaching:
        CheckAttaching();
        SwitchLevel();
        game_state = Spawn;
        break;
      case GameOver:
        ResetGameInfo();
        game_state = GameStart;
        break;
      case GameTerminate:
        break;
    }
  }
}

int Timer() {
  static clock_t moving_start = 0, moving_end = 0;
  GameInfo_t *game_info = GetGameInfo();
  int rtrn = 0;
  if (moving_start == 0) {
    moving_start = moving_end = clock();
  } else {
    moving_end = clock();
    double time_diff =
        ((double)(moving_end - moving_start)) / CLOCKS_PER_SEC * 1000;
    if (time_diff >= game_info->speed) {
      rtrn = 1;
      moving_start = moving_end = 0;
    }
  }
  return rtrn;
}

void SwitchLevel() {
  GameInfo_t *game_info = GetGameInfo();
  game_info->level = game_info->level <= 10 ? (game_info->score / 600) + 1 : 10;
  game_info->speed = 740 - 40 * game_info->level;
}
