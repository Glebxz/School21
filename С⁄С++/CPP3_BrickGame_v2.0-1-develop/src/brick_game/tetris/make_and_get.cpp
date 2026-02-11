#include "s21_tetris.h"

GameInfo_t *GetGameInfo() {
  static GameInfo_t game_info = {};
  GameInfo_t *ptr_game_info = &game_info;
  return ptr_game_info;
}

Figure_t *GetNextFigure() {
  static Figure_t next_figure = {};
  Figure_t *ptr_next_figure = &next_figure;
  return ptr_next_figure;
}

Figure_t *GetCurrentFigure() {
  static Figure_t current_figure = {};
  Figure_t *ptr_current_figure = &current_figure;
  return ptr_current_figure;
}

void MakeGameInfo() {
  GameInfo_t *ptr_game_info = GetGameInfo();
  ptr_game_info->field = MakeField(length_field, width_field);
  ptr_game_info->next = MakeField(4, 4);
  UpdateHighScore();
  ptr_game_info->level = 1;
  ptr_game_info->speed = 700;
  ResetNextFigure();
  ResetNextPtr();
}

int **MakeField(int rows, int cols) {
  size_t memory_length = rows * sizeof(int *) + rows * cols * sizeof(int);
  int **field = static_cast<int **>(calloc(memory_length, 1));
  if (field != NULL) {
    int *ptr_rows = (int *)((char *)field + rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
      field[i] = ptr_rows + i * cols;
    }
  } else {
    userInput(Terminate, 0);
  }
  return field;
}

void ResetNextFigure() {
  Figure_t *next_figure = GetNextFigure();
  *next_figure = MakeRandomFigure();
}

void ResetCurrentFigure() {
  Figure_t *current_figure = GetCurrentFigure();
  *current_figure = *GetNextFigure();
}

void ResetNextPtr() {
  GameInfo_t *game_info = GetGameInfo();
  Figure_t *next_figure = GetNextFigure();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game_info->next[i][j] = next_figure->arry[i][j];
    }
  }
}

void SpawnReset() {
  ResetCurrentFigure();
  ResetNextFigure();
  ResetNextPtr();
}

Figure_t MakeRandomFigure() {
  Figure_t figure = {};
  int all_figures[7][4][4] = {
      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {0, 0, 0, 1}, {0, 1, 1, 1}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}},

      {{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}}};
  int type = rand() % 7;
  figure.figure_type = static_cast<FigureType_t>(type + 1);
  int k = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (all_figures[type][i][j] == 1) {
        figure.point[k].coord_x = j + 3;
        figure.point[k].coord_y = i - 1;
        figure.arry[i][j] = type + 1;
        k++;
      }
    }
  }
  SetRotationCenter(&figure);
  return figure;
}

void SetRotationCenter(Figure_t *figure) {
  switch (figure->figure_type) {
  case L:
    figure->rotation_center.coord_x = figure->point[0].coord_x - 1;
    figure->rotation_center.coord_y = figure->point[0].coord_y;
    break;
  case J:
    figure->rotation_center.coord_x = figure->point[0].coord_x + 1;
    figure->rotation_center.coord_y = figure->point[0].coord_y;
    break;
  case S:
    figure->rotation_center.coord_x = figure->point[0].coord_x;
    figure->rotation_center.coord_y = figure->point[0].coord_y;
    break;
  case Z:
    figure->rotation_center.coord_x = figure->point[1].coord_x;
    figure->rotation_center.coord_y = figure->point[1].coord_y;
    break;
  case T:
    figure->rotation_center.coord_x = figure->point[2].coord_x;
    figure->rotation_center.coord_y = figure->point[2].coord_y;
    break;
  default:
    break;
  }
}

void UpdateHighScore() {
  GameInfo_t *game_info = GetGameInfo();
  FILE *file_high_score = fopen("high_score.txt", "r");
  if (file_high_score == NULL) {
    file_high_score = fopen("high_score.txt", "w");
    fprintf(file_high_score, "%d", 0);
    fclose(file_high_score);
  } else {
    int high_score = 0;
    fscanf(file_high_score, "%d", &high_score);
    fclose(file_high_score);
    game_info->high_score = high_score;
  }
}

void FreeMemory() {
  GameInfo_t *game_info = GetGameInfo();
  free(game_info->field);
  free(game_info->next);
}

void ResetGameInfo() {
  GameInfo_t *game_info = GetGameInfo();
  for (int i = 0; i < length_field; i++) {
    for (int j = 0; j < width_field; j++) {
      game_info->field[i][j] = 0;
    }
  }
  game_info->score = 0;
  game_info->level = 1;
  game_info->speed = 700;
  game_info->pause = 0;
}
