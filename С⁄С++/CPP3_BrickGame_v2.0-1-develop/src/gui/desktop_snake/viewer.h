#ifndef VIEWER_H
#define VIEWER_H

#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <sstream>
#include <string>
#include "api.h"
#include "print_classes.h"

class Controller : public QWidget {
    Q_OBJECT
public:
    Controller(QWidget *parent) : QWidget(parent) {
        this->setFocus();
    }
    void NextTurn(){
        userInput(static_cast<UserAction_t>(100), 0);
    }
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // VIEWER_H
