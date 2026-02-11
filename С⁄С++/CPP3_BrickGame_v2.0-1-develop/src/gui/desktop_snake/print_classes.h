#ifndef PRINT_CLASSES_H
#define PRINT_CLASSES_H

#include "viewer.h"

class GameControlPanel : public QLabel{
    Q_OBJECT

public:
    GameControlPanel(QWidget *parent) : QLabel(parent) {
        this->setFixedSize(209, 419);
        this->setText("Strat: [s]\nPause: [p]\nTerminate: [t]\nMoving: [arrow buttons]\nAction: [space]\n");
        this->setAlignment(Qt::AlignCenter);
    }
};

class GameScorePanel : public QWidget {
    Q_OBJECT
    QWidget *next;
    QLabel *score;
    QVBoxLayout *layout;
    QGridLayout *grid_layout;
    QWidget *NextFigure[4][4];

public:
    void UpdateScore();
    GameScorePanel(QWidget *parent) : QWidget(parent) {
        this->setFixedSize(200, 419);
        next = new QWidget(this);
        next->setFixedSize(83, 83);
        score = new QLabel(this);
        score->setFixedSize(200, 419);
        score->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        layout = new QVBoxLayout(this);
        layout->addWidget(next);
        layout->addWidget(score);
        grid_layout = new QGridLayout(next);
        grid_layout->setContentsMargins(0, 0, 0, 0);
        grid_layout->setSpacing(1);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                NextFigure[i][j] = new QWidget(next);
                NextFigure[i][j]->setFixedSize(20, 20);
                NextFigure[i][j]->setStyleSheet("background-color: white;");
                grid_layout->addWidget(NextFigure[i][j], i, j);
            }
        }
    }
};

class GameFieldPanel : public QWidget {
    Q_OBJECT
    QWidget *GameField[20][10];
    QGridLayout *layout = nullptr;

public:
    GameFieldPanel(QWidget *parent);
    void UpdateField();
};

#endif
