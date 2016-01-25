#include "controller.h"
#include "game.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>

Controller::Controller(Game *game, QWidget *parent):QWidget(parent),_game(game)
{
    auto button1 = new QPushButton("Start");
    auto button2 = new QPushButton("Pause");
    auto button3 = new QPushButton("Reset");
    auto speed = new QSlider(Qt::Horizontal	);
    speed->setMinimum(1);
    speed->setMaximum(100);
    speed->setTickInterval(1);
    speed->setValue(game->speed());
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    layout->addWidget(speed);

    setLayout(layout);

    connect(button1,SIGNAL(clicked()),this,SLOT(start()));
    connect(button2,SIGNAL(clicked()),this,SLOT(pause()));
    connect(button3,SIGNAL(clicked()),this,SLOT(reset()));

    connect(speed,SIGNAL(valueChanged(int)),this, SLOT(changeSpeed(int)));

}
void Controller::start() {
    _game->start();
}

void Controller::pause(){
    _game->pause();
}

void Controller::reset(){
    _game->reset();
}
void Controller::changeSpeed( int speed ) {
    _game->setSpeed( speed );
}
