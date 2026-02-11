#include "s21_tetris.h"

void CheckAttaching() {
  GameInfo_t *game_info = GetGameInfo();
  int attach_score = 0, summ = 0;
  for (int i = length - 1; i >= 0; i--) {
    for (int j = 0; j < width; j++) {
      if (game_info->field[i][j] >= 1) {
        summ++;
      }
    }
    if (summ == 10) {
      attach_score = CalcScore(attach_score);
      RemoveAttach(i);
      i++;
    }
    summ = 0;
  }
  game_info->score += attach_score;
  if (game_info->score > game_info->high_score) {
    FILE *file_high_score = fopen("high_score.txt", "w");
    fprintf(file_high_score, "%d", game_info->score);
    fclose(file_high_score);
    game_info->high_score = game_info->score;
  }
}

int CalcScore(int attach_score) {
  int rtrn = 0;
  switch (attach_score) {
    case 0:
      rtrn = 100;
      break;
    case 100:
      rtrn = 300;
      break;
    case 300:
      rtrn = 700;
      break;
    case 700:
      rtrn = 1500;
      break;
    case 1500:
      rtrn = 1500;
      break;
  }
  return rtrn;
}

void RemoveAttach(int row) {
  GameInfo_t *game_info = GetGameInfo();
  for (int i = row; i > 0; i--) {
    for (int j = 0; j < width; j++) {
      game_info->field[i][j] = game_info->field[i - 1][j];
    }
  }
  for (int j = 0; j < width; j++) {
    game_info->field[0][j] = 0;
  }
}
