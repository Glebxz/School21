#include "api.h"
#include "viewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *main = new QWidget;
    main->setWindowTitle("Brick Game");
    main->setFixedSize(650, 500);

    GameControlPanel *game_control = new GameControlPanel(main);
    GameFieldPanel *game_field = new GameFieldPanel(main);
    GameScorePanel *game_score = new GameScorePanel(main);

    QHBoxLayout *main_layout = new QHBoxLayout(main);
    main_layout->addWidget(game_control);
    main_layout->addWidget(game_field);
    main_layout->addWidget(game_score);

    Controller *control = new Controller(main);


    QTimer timer;
    timer.start(0);
    QObject::connect(&timer, &QTimer::timeout, control, &Controller::NextTurn);
    QObject::connect(&timer, &QTimer::timeout, game_field, &GameFieldPanel::UpdateField);
    QObject::connect(&timer, &QTimer::timeout, game_score, &GameScorePanel::UpdateScore);

    main->show();

    return a.exec();
}
