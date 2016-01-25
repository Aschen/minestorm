#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>

#include "Controller.hh"
#include "Display.hh"

Controller::Controller(Display *display, QWidget *parent)
    : QWidget(parent),
      _display(display)
{
    auto button1 = new QPushButton("Start");
    auto button2 = new QPushButton("Pause");
    auto button3 = new QPushButton("Reset");
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    setLayout(layout);

    connect(button1, SIGNAL(clicked()), this, SLOT(start()));
    connect(button2, SIGNAL(clicked()), this, SLOT(pause()));
    connect(button3, SIGNAL(clicked()), this, SLOT(reset()));
}
void Controller::start()
{
    _display->start();
}

void Controller::pause()
{
    _display->pause();
}

void Controller::reset()
{
    _display->reset();
}
