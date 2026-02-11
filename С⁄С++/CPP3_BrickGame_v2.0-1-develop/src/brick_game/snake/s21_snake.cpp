#include "s21_snake.h"

void SnakeGameModel::FSM(UserAction_t action) {
  if (action == Pause) {
    game_info_.pause = game_info_.pause == 0 ? 1 : 0;
  }
  if (game_info_.pause != 1) {
    switch (game_state_) {
    case GameStart:
      game_state_ = action == Start ? SpawnNewApple : GameStart;
      break;
    case SpawnNewApple:
      SpawnApple();
      game_state_ = ChoseDirection;
      break;
    case ChoseDirection:
      ChangeDirection(action);
      game_state_ =
          Timer(action == Action) == true ? StepForward : ChoseDirection;
      break;
    case StepForward:
      if (CheckEatApple() == true) {
        SnakeGrow();
        SetScore();
        game_state_ = CheckWin() == true ? GameOver : SpawnNewApple;
      } else {
        MoveForward();
        game_state_ = (CheckCollisionWalls() + CheckCollisionBody() > 0)
                          ? GameOver
                          : ChoseDirection;
      }
      break;
    case GameOver:
      ResetGame();
      game_state_ = GameStart;
      break;
    case GameTerminate:
      break;
    default:
      break;
    }
  }
}

bool SnakeGameModel::Timer(bool action) {
  std::chrono::nanoseconds period{
      (action == true ? game_info_.speed / 2 : game_info_.speed) * 1000000};
  std::chrono::time_point<std::chrono::steady_clock> end_timer =
      std::chrono::steady_clock::now();
  if (start_timer_.time_since_epoch().count() == 0) {
    start_timer_ = std::chrono::steady_clock::now();
  } else if ((end_timer - start_timer_) > period) {
    start_timer_ = end_timer = std::chrono::steady_clock::now();
    return true;
  }
  return false;
}

void SnakeGameModel::SpawnApple() {
  while (1) {
    apple_.coord_x_ = std::rand() % width_field;
    apple_.coord_y_ = std::rand() % length_field;
    if (game_info_.field[apple_.coord_y_][apple_.coord_x_] == 0) {
      game_info_.field[apple_.coord_y_][apple_.coord_x_] = apple_.color_;
      break;
    }
  }
}

void SnakeGameModel::SetScore() {
  game_info_.score = Snake_.size() - 4;
  if (game_info_.score > game_info_.high_score) {
    FILE *file_high_score = std::fopen("high_score.txt", "w");
    std::fprintf(file_high_score, "%d", game_info_.score);
    std::fclose(file_high_score);
    game_info_.high_score = game_info_.score;
  }
  UpdateHighScore();
  game_info_.level = (game_info_.score / 5) <= 10 ? (game_info_.score / 5) : 10;
  game_info_.speed = BASE_SPEED - game_info_.level * 20;
}

bool SnakeGameModel::CheckWin() {
  return game_info_.score == 200 ? true : false;
}

void SnakeGameModel::UpdateHighScore() {
  FILE *file_high_score = std::fopen("high_score.txt", "r");
  if (file_high_score == NULL) {
    file_high_score = std::fopen("high_score.txt", "w");
    std::fprintf(file_high_score, "%d", 0);
    std::fclose(file_high_score);
  } else {
    int high_score = 0;
    std::fscanf(file_high_score, "%d", &high_score);
    std::fclose(file_high_score);
    game_info_.high_score = high_score;
  }
}

GameInfo_t &SnakeGameModel::GetGameInfo() {
  for (int i = 0; i < length_field; i++) {
    for (int j = 0; j < width_field; j++) {
      game_info_.field[i][j] = 0;
    }
  }
  for (Snake::iterator iter = Snake_.begin(); iter != Snake_.end(); iter++) {
    if (!(iter->coord_x_ >= width_field || iter->coord_x_ < 0 ||
          iter->coord_y_ >= length_field || iter->coord_y_ < 0)) {
      game_info_.field[iter->coord_y_][iter->coord_x_] = iter->color_;
    }
  }
  if (game_state_ != GameStart) {
    game_info_.field[apple_.coord_y_][apple_.coord_x_] = apple_.color_;
  }
  return game_info_;
}

SnakeGameModel *GetGameModel() {
  static SnakeGameModel model;
  SnakeGameModel *ptr_model = &model;
  return ptr_model;
}

void userInput(UserAction_t action, bool hold) {
  GetGameModel()->FSM(action);
  hold = -hold;
}

GameInfo_t updateCurrentState() {
  SnakeGameModel *model = GetGameModel();
  GameInfo_t game_info = model->GetGameInfo();
  return game_info;
}

void SnakeGameModel::ResetGame() {
  Snake_.clear();
  Snake_.push_back({5, 8, 1});
  Snake_.push_back({5, 9, 2});
  Snake_.push_back({5, 10, 3});
  Snake_.push_back({5, 11, 4});
  move_pattern_ = MoveUp;
  game_info_.score = 0;
  game_info_.level = 0;
  game_info_.speed = BASE_SPEED;
}