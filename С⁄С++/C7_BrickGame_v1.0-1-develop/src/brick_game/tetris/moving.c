#include "s21_tetris.h"

void Move(UserAction_t action) {
  RemoveFigureFromField();
  switch (action) {
    case Left:
      MoveLeft();
      break;
    case Right:
      MoveRight();
      break;
    case Down:
      MoveDown();
      break;
    case Action:
      MoveAction();
      break;
    default:
      break;
  }
  PutFigureOnField();
}

void MoveLeft() {
  Figure_t* current_figure = GetCurrentFigure();
  Figure_t tmp_current_figure = *current_figure;
  for (int k = 0; k < 4; k++) {
    current_figure->point[k].coord_x--;
  }
  current_figure->rotation_center.coord_x--;
  if (CheckCanMove()) {
    *current_figure = tmp_current_figure;
  }
}

void MoveRight() {
  Figure_t* current_figure = GetCurrentFigure();
  Figure_t tmp_current_figure = *current_figure;
  for (int k = 0; k < 4; k++) {
    current_figure->point[k].coord_x++;
  }
  current_figure->rotation_center.coord_x++;
  if (CheckCanMove()) {
    *current_figure = tmp_current_figure;
  }
}

int MoveDown() {
  Figure_t* current_figure = GetCurrentFigure();
  Figure_t tmp_current_figure = *current_figure;
  int rtrn = 0;
  for (int k = 0; k < 4; k++) {
    current_figure->point[k].coord_y++;
  }
  current_figure->rotation_center.coord_y++;
  if (CheckCanMove()) {
    *current_figure = tmp_current_figure;
    rtrn = 1;
  }
  return rtrn;
}

void MoveAction() {
  Figure_t* current_figure = GetCurrentFigure();
  switch (current_figure->figure_type) {
    case O:
      break;
    case I:
      RotateI();
      break;
    default:
      RotateLJSZT();
      break;
  }
}

int CheckCanMove() {
  if (CheckOutOfField()) {
    return 1;
  }
  if (CheckCollision()) {
    return 1;
  }
  return 0;
}

int CheckOutOfField() {
  Figure_t* current_figure = GetCurrentFigure();
  int check_out_of_field = 0;
  for (int k = 0; k < 4 && check_out_of_field == 0; k++) {
    check_out_of_field += current_figure->point[k].coord_x <= -1 ||
                          current_figure->point[k].coord_x >= 10 ||
                          current_figure->point[k].coord_y <= -1 ||
                          current_figure->point[k].coord_y >= 20;
  }
  return check_out_of_field;
}

int CheckCollision() {
  Figure_t* current_figure = GetCurrentFigure();
  GameInfo_t* game_info = GetGameInfo();
  int check_collision = 0;
  for (int k = 0; k < 4 && check_collision == 0; k++) {
    check_collision = game_info->field[current_figure->point[k].coord_y]
                                      [current_figure->point[k].coord_x];
  }
  return check_collision == 0 ? 0 : 1;
}

void PutFigureOnField() {
  Figure_t* current_figure = GetCurrentFigure();
  GameInfo_t* game_info = GetGameInfo();
  for (int k = 0; k < 4; k++) {
    game_info->field[current_figure->point[k].coord_y]
                    [current_figure->point[k].coord_x] =
        current_figure->figure_type;
  }
}

void RemoveFigureFromField() {
  Figure_t* current_figure = GetCurrentFigure();
  GameInfo_t* game_info = GetGameInfo();
  for (int k = 0; k < 4; k++) {
    game_info->field[current_figure->point[k].coord_y]
                    [current_figure->point[k].coord_x] = 0;
  }
}
