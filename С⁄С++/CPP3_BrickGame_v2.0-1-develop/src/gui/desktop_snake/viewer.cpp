#include "viewer.h"

void Controller::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_S:
      userInput(Start, 0);
      break;
    case Qt::Key_P:
      userInput(Pause, 0);
      break;
    case Qt::Key_T:
      userInput(Terminate, 0);
      QCoreApplication::quit();
      break;
    case Qt::Key_Left:
      userInput(Left, 0);
      break;
    case Qt::Key_Right:
      userInput(Right, 0);
      break;
    case Qt::Key_Up:
      userInput(Up, 0);
      break;
    case Qt::Key_Down:
      userInput(Down, 0);
      break;
    case Qt::Key_Space:
      userInput(Action, 0);
      break;
    default:
      userInput(static_cast<UserAction_t>(100), 0);
      break;
    }
}
