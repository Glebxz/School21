#ifndef BRICKGAME_SNAKE_s21SNAKE_H
#define BRICKGAME_SNAKE_s21SNAKE_H

#include <chrono>
#include <deque>
#include <random>

#include "api.h"

#define length_field 20
#define width_field 10
#define BASE_SPEED 400

/**
 * @brief Главный класс со всей логикой игры
 * @param Snake_ объект, представляющий тело змейки в виде очереди std::deque
 * @param move_pattern паттерн текущего направления движения змейки
 * @param start_timer_ хранит в себе начало отсчета таймера
 * @param game_state_ текущее стостоянии игры
 * @param game_info_ объект структуры с информацией о текущем состоянии игры
 * @st
 */
class SnakeGameModel {
private:
  /**
   * @brief Структура хранит координаты каждого элемента тела змейки
   * @param coord_x_ координата Х
   * @param coord_y_ координата У
   * @param color_ цвет
   */
  struct SnakeCell {
    int coord_x_ = 5;
    int coord_y_ = 5;
    int color_ = 7;
  };

  std::deque<SnakeCell> Snake_{{5, 8, 1}, {5, 9, 2}, {5, 10, 3}, {5, 11, 4}};
  int move_pattern_ = MoveUp;
  SnakeCell apple_;
  std::chrono::time_point<std::chrono::steady_clock> start_timer_{};

  GameInfo_t game_info_;

public:
  int game_state_ = 0;
  using Snake = std::deque<SnakeCell>;

  /**
   * @brief Перечисление всех возможных паттернов движения
   */
  enum MovePattern { MoveUp = 0, MoveDown, MoveLeft, MoveRight };

  /**
   * @brief Перечисление всех возможных конечных состояний игры.
   */
  enum GameState_t {
    GameStart = 0,
    SpawnNewApple,
    ChoseDirection,
    StepForward,
    GameOver,
    GameTerminate
  };

  /**
   * @brief Конструктор класса
   */
  SnakeGameModel() {
    game_info_.field = new int *[length_field] {};
    for (int i = 0; i < length_field; i++) {
      game_info_.field[i] = new int[width_field]{};
    }
    std::srand(time(NULL));
    game_info_.next = nullptr;
    game_info_.score = 0;
    UpdateHighScore();
    game_info_.level = 0;
    game_info_.speed = BASE_SPEED;
    game_info_.pause = 0;
  }

  /**
   * @brief Деструктор класса
   */
  ~SnakeGameModel() {
    for (int i = 0; i < length_field; i++) {
      delete[] game_info_.field[i];
    }
    delete[] game_info_.field;
  }

  /**
   * @brief Собирает всю информацию о текущем состоянии игры в виде структуры
   * GameInfo_t
   * @return Ссылку на эту структуру
   */
  GameInfo_t &GetGameInfo();

  /**
   * @brief Функция для обработки конечных состояний и перехода по ним
   * @param Текущее действие пользователя
   */
  void FSM(UserAction_t action);

  /**
   * @brief Спавнит новое яблоко в случайном месте
   */
  void SpawnApple();

  /**
   * @brief Меняет move_pattern в зависимости от action
   * @param Текущее действие пользователя
   */
  void ChangeDirection(UserAction_t action);

  /**
   * @brief Таймеры игры
   * @param проверка на наличие действия Action, если true то дельта тайм будет
   * в 2 раза меньше
   */
  bool Timer(bool action);

  /**
   * @brief Проверяет будет ли непосредственно перед следующим ходом сьедено
   * яблоко
   * @return true если яблоко будет сьедено
   */
  bool CheckEatApple();

  /**
   * @brief Рост змейки на 1 клетку после поедания яблока
   */
  void SnakeGrow();

  /**
   * @brief Устанавливает все поля счета игры в зависимости от размера змейки
   */
  void SetScore();

  /**
   * @brief Проверяет размер змейки, если достигнуто 200 очков засчтывается
   * победа
   * @return true если достигнуто 200 очков
   */
  bool CheckWin();

  /**
   * @brief Двигает змейку вперед на 1 клетку в зависимости от move_pattern_
   */
  void MoveForward();

  /**
   * @brief проверка на столкновение с рамками игрового поля
   * @return true если произошло столкновение
   */
  bool CheckCollisionWalls();

  /**
   * @brief проверка на столкновение змейки с собственным телом
   * @return true если произошло столкновение
   */
  bool CheckCollisionBody();

  /**
   * @brief Обновление информации в файле, хранящем рекордный результат
   */
  void UpdateHighScore();

  /**
   * @brief перезагрузка игры в случае победы или поражения
   */
  void ResetGame();
};

#endif