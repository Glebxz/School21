#include "s21_tetris.h"

void RotateLJSZT() {
  Figure_t* current_figure = GetCurrentFigure();
  Figure_t tmp_current_figure = *current_figure;
  for (int k = 0; k < 4; k++) {
    if (current_figure->point[k].coord_x ==
            current_figure->rotation_center.coord_x - 1 &&
        current_figure->point[k].coord_y ==
            current_figure->rotation_center.coord_y - 1) {
      current_figure->point[k].coord_x += 2;
    } else if (current_figure->point[k].coord_x ==
                   current_figure->rotation_center.coord_x &&
               current_figure->point[k].coord_y ==
                   current_figure->rotation_center.coord_y - 1) {
      current_figure->point[k].coord_x++;
      current_figure->point[k].coord_y++;
    } else if (current_figure->point[k].coord_x ==
                   current_figure->rotation_center.coord_x + 1 &&
               current_figure->point[k].coord_y ==
                   current_figure->rotation_center.coord_y - 1) {
      current_figure->point[k].coord_y += 2;
    } else if (current_figure->point[k].coord_x ==
                   current_figure->rotation_center.coord_x + 1 &&
               current_figure->point[k].coord_y ==
                   current_figure->rotation_center.coord_y) {
      current_figure->point[k].coord_y++;
      current_figure->point[k].coord_x--;
    } else if (current_figure->point[k].coord_x ==
                   current_figure->rotation_center.coord_x + 1 &&
               current_figure->point[k].coord_y ==
                   current_figure->rotation_center.coord_y + 1) {
      current_figure->point[k].coord_x -= 2;
    } else if (current_figure->point[k].coord_x ==
                   current_figure->rotation_center.coord_x &&
               current_figure->point[k].coord_y ==
                   current_figure->rotation_center.coord_y + 1) {
      current_figure->point[k].coord_x--;
      current_figure->point[k].coord_y--;
    } else if (current_figure->point[k].coord_x ==
                   current_figure->rotation_center.coord_x - 1 &&
               current_figure->point[k].coord_y ==
                   current_figure->rotation_center.coord_y + 1) {
      current_figure->point[k].coord_y -= 2;
    } else if (current_figure->point[k].coord_x ==
                   current_figure->rotation_center.coord_x - 1 &&
               current_figure->point[k].coord_y ==
                   current_figure->rotation_center.coord_y) {
      current_figure->point[k].coord_y--;
      current_figure->point[k].coord_x++;
    }
  }
  if (CheckCanMove()) {
    *current_figure = tmp_current_figure;
  }
}

void RotateI() {
  Figure_t* current_figure = GetCurrentFigure();
  Figure_t tmp_current_figure = *current_figure;
  switch (current_figure->rotation_stage_for_I) {
    case 0:
      current_figure->point[0].coord_x += 2;
      current_figure->point[0].coord_y--;
      current_figure->point[3].coord_x = current_figure->point[2].coord_x =
          current_figure->point[1].coord_x = current_figure->point[0].coord_x;
      current_figure->point[1].coord_y = current_figure->point[0].coord_y + 1;
      current_figure->point[2].coord_y = current_figure->point[1].coord_y + 1;
      current_figure->point[3].coord_y = current_figure->point[2].coord_y + 1;
      current_figure->rotation_stage_for_I = 1;
      break;
    case 1:
      current_figure->point[0].coord_x++;
      current_figure->point[0].coord_y += 2;
      current_figure->point[3].coord_y = current_figure->point[2].coord_y =
          current_figure->point[1].coord_y = current_figure->point[0].coord_y;
      current_figure->point[1].coord_x = current_figure->point[0].coord_x - 1;
      current_figure->point[2].coord_x = current_figure->point[1].coord_x - 1;
      current_figure->point[3].coord_x = current_figure->point[2].coord_x - 1;
      current_figure->rotation_stage_for_I = 2;
      break;
    case 2:
      current_figure->point[0].coord_x -= 2;
      current_figure->point[0].coord_y++;
      current_figure->point[3].coord_x = current_figure->point[2].coord_x =
          current_figure->point[1].coord_x = current_figure->point[0].coord_x;
      current_figure->point[1].coord_y = current_figure->point[0].coord_y - 1;
      current_figure->point[2].coord_y = current_figure->point[1].coord_y - 1;
      current_figure->point[3].coord_y = current_figure->point[2].coord_y - 1;
      current_figure->rotation_stage_for_I = 3;
      break;
    case 3:
      current_figure->point[0].coord_x--;
      current_figure->point[0].coord_y -= 2;
      current_figure->point[3].coord_y = current_figure->point[2].coord_y =
          current_figure->point[1].coord_y = current_figure->point[0].coord_y;
      current_figure->point[1].coord_x = current_figure->point[0].coord_x + 1;
      current_figure->point[2].coord_x = current_figure->point[1].coord_x + 1;
      current_figure->point[3].coord_x = current_figure->point[2].coord_x + 1;
      current_figure->rotation_stage_for_I = 0;
      break;
    default:
      break;
  }
  if (CheckCanMove()) {
    *current_figure = tmp_current_figure;
  }
}
