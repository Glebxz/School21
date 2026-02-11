#include "s21_snake.h"

void SnakeGameModel::ChangeDirection(UserAction_t action) {
  if (action == Up && move_pattern_ == MoveDown) {
    return;
  }
  if (action == Down && move_pattern_ == MoveUp) {
    return;
  }
  if (action == Left && move_pattern_ == MoveRight) {
    return;
  }
  if (action == Right && move_pattern_ == MoveLeft) {
    return;
  }
  switch (action) {
  case Up:
    move_pattern_ = MoveUp;
    break;
  case Down:
    move_pattern_ = MoveDown;
    break;
  case Left:
    move_pattern_ = MoveLeft;
    break;
  case Right:
    move_pattern_ = MoveRight;
    break;
  default:
    break;
  }
}

void SnakeGameModel::MoveForward() {
  SnakeCell tmp = Snake_.front();
  switch (move_pattern_) {
  case MoveUp:
    --Snake_.front().coord_y_;
    break;
  case MoveDown:
    ++Snake_.front().coord_y_;
    break;
  case MoveLeft:
    --Snake_.front().coord_x_;
    break;
  case MoveRight:
    ++Snake_.front().coord_x_;
    break;
  default:
    break;
  }

  Snake::iterator iter = Snake_.begin();
  iter++;
  while (iter != Snake_.end()) {
    std::swap(tmp.coord_x_, iter->coord_x_);
    std::swap(tmp.coord_y_, iter->coord_y_);
    iter++;
  }
}

bool SnakeGameModel::CheckCollisionWalls() {
  for (Snake::iterator iter = Snake_.begin(); iter != Snake_.end(); iter++) {
    if (iter->coord_x_ >= width_field || iter->coord_x_ < 0 ||
        iter->coord_y_ >= length_field || iter->coord_y_ < 0) {
      return true;
    }
  }
  return false;
}

bool SnakeGameModel::CheckCollisionBody() {
  Snake::iterator iter = Snake_.begin();
  iter++;
  while (iter != Snake_.end()) {
    if (Snake_.front().coord_x_ == iter->coord_x_ &&
        Snake_.front().coord_y_ == iter->coord_y_) {
      return true;
    }
    iter++;
  }
  return false;
}

bool SnakeGameModel::CheckEatApple() {
  switch (move_pattern_) {
  case MoveUp:
    return Snake_.front().coord_x_ == apple_.coord_x_ &&
           Snake_.front().coord_y_ == apple_.coord_y_ + 1;
  case MoveDown:
    return Snake_.front().coord_x_ == apple_.coord_x_ &&
           Snake_.front().coord_y_ == apple_.coord_y_ - 1;
  case MoveLeft:
    return Snake_.front().coord_x_ == apple_.coord_x_ + 1 &&
           Snake_.front().coord_y_ == apple_.coord_y_;
  case MoveRight:
    return Snake_.front().coord_x_ == apple_.coord_x_ - 1 &&
           Snake_.front().coord_y_ == apple_.coord_y_;
  default:
    return false;
  }
  return false;
}

void SnakeGameModel::SnakeGrow() {
  Snake_.push_front(apple_);
  Snake_.front().color_ = std::rand() % 6 + 1;
}