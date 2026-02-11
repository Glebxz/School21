#ifndef API_H
#define API_H

#include <stdbool.h>

/**
 * @brief Перечисление всех действий пользователя, принимаемых на вход.
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief Структура для хранения информации о текущем состоянии игры.
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Функция для вызова в пользовательском интерфейсе, которая обрабатывает
 * действия игрока
 * @param action пользовательское действие
 * @param hold параметр, отвечающий за зажатие клавиши (не используется)
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Функция для вызова в пользовательском интерфейсе, обновляет информацию
 * о текущем состоянии игры
 * @return Возвращает структуру с данными о текущем состоянии игры
 */
GameInfo_t updateCurrentState();

#include "s21_tetris.h"

#endif