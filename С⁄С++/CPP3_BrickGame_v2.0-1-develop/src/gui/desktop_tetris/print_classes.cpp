#include "print_classes.h"

GameFieldPanel::GameFieldPanel(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);
    this->setFixedSize(209, 419);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(1);
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            GameField[i][j] = new QWidget(this);
            GameField[i][j]->setFixedSize(20, 20);
            GameField[i][j]->setStyleSheet("background-color: white;");
            layout->addWidget(GameField[i][j], i, j);
        }
    }
}

void GameFieldPanel::UpdateField() {
    GameInfo_t game_info = updateCurrentState();
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            switch (game_info.field[i][j]) {
            case 0:
                GameField[i][j]->setStyleSheet("background-color: white;");
                break;
            case 1:
                GameField[i][j]->setStyleSheet("background-color: red;");
                break;
            case 2:
                GameField[i][j]->setStyleSheet("background-color: olive;");
                break;
            case 3:
                GameField[i][j]->setStyleSheet("background-color: yellow;");
                break;
            case 4:
                GameField[i][j]->setStyleSheet("background-color: purple;");
                break;
            case 5:
                GameField[i][j]->setStyleSheet("background-color: orange;");
                break;
            case 6:
                GameField[i][j]->setStyleSheet("background-color: blue;");
                break;
            case 7:
                GameField[i][j]->setStyleSheet("background-color: green;");
                break;
            default:
                break;
            }

        }
    }
}

void GameScorePanel::UpdateScore() {
    GameInfo_t game_info = updateCurrentState();
    if (game_info.next != nullptr) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (game_info.next[i][j] > 0) {
                NextFigure[i][j]->setStyleSheet("background-color: black;");
            }
        }
    }
    }
    std::ostringstream oss;
    oss << "Current score: " << game_info.score << std::endl << "High score: " << game_info.high_score << std::endl  << "Level: " << game_info.level << std::endl << "Speed: " << game_info.speed << std::endl;
    std::string result = oss.str();
    QString q_result = QString(result.c_str());
    score->setText(q_result);
}

