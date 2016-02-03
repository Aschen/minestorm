#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>

#include "Controller.hh"
#include "Display.hh"

Controller::Controller(Display *display, QWidget *parent)
    : QWidget(parent),
      _display(display),
      _inputHost(new QLineEdit("localhost", this)),
      _coreRunner(QSharedPointer<CoreRunner>(new CoreRunner(20)))
{
    auto startNewGame = new QPushButton("New Game", this);
    auto joinGame = new QPushButton("Join Game", this);
    auto exitGame = new QPushButton("Quit", this);

    QHBoxLayout *layout = new QHBoxLayout(this);

    layout->addWidget(startNewGame);
    layout->addWidget(joinGame);
    layout->addWidget(_inputHost);
    layout->addWidget(exitGame);

    setLayout(layout);

    connect(startNewGame,   SIGNAL(clicked()), this, SLOT(startNewGame()));
    connect(joinGame,       SIGNAL(clicked()), this, SLOT(joinGame()));
    connect(exitGame,       SIGNAL(clicked()), this, SLOT(exitGame()));
}

void Controller::startNewGame()
{
    _coreRunner->start();
    _display->startNewGame();
}

void Controller::joinGame()
{
    _display->joinGame(_inputHost->text());
}

void Controller::exitGame()
{
    _coreRunner.clear();
    _display->exitGame();
}
