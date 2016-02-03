#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <iostream>

#include "GameBoard.hh"
#include "Display.hh"

GameBoard::GameBoard(Display *display,QWidget *parent)
    : QWidget(parent),
      _display(display)
{
    connect(_display, SIGNAL(changed()), this, SLOT(update()));
    setMinimumSize(_display->size());
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

void GameBoard::paintEvent(QPaintEvent * /* event */ )
{
    QPainter painter;
    painter.begin(this);
    auto rectT = rect();
    _display->draw(painter, rectT);
    painter.end();
}

void GameBoard::mousePressEvent (QMouseEvent * event)
{
    event->accept();
    // normalise les coordonnées pour le remettre à la taille du jeu
    auto x = event->x() * _display->size().width() / (double) rect().width();
    auto y = event->y() * _display->size().height() / (double) rect().height();
    _display->mousePressed(x, y);
}

void GameBoard::keyPressEvent(QKeyEvent * event)
{
    _display->keyPressed(event->key());
}

void GameBoard::keyReleaseEvent(QKeyEvent * event)
{
    _display->keyReleased(event->key());
}
