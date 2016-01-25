#include "gameboard.h"
#include "game.h"

#include <QPainter>
#include <QColor>
#include <QMouseEvent>

#include <iostream>

GameBoard::GameBoard(Game *game,QWidget *parent) :
    QWidget(parent),_game(game)
{
    connect(_game,SIGNAL(changed()),this,SLOT(update()));
    setMinimumSize(_game->size());
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

}
void GameBoard::paintEvent(QPaintEvent * /* event */ ) {
    QPainter painter;
    painter.begin(this);
    auto rectT = rect();
    _game->draw(painter, rectT);
    painter.end();
}
void GameBoard::mousePressEvent ( QMouseEvent * event ) {
    event->accept();
    // normalise les coordonnées pour le remettre à la taille du jeu
    auto x = event->x() * _game->size().width() / (double)rect().width()  ;
    auto y = event->y() * _game->size().height() / (double)rect().height() ;
    _game->mousePressed(x,y);
}
void GameBoard::keyPressEvent ( QKeyEvent * event ) {
    _game->keyPressed(event->key());
}
void GameBoard::keyReleaseEvent ( QKeyEvent * event ) {
    _game->keyReleased(event->key());
}
void GameBoard::mouseMoveEvent(QMouseEvent * event) {
    event->accept();
    auto x = event->x() * _game->size().width() / (double)rect().width()  ;
    auto y = event->y() * _game->size().height() / (double)rect().height() ;
    _game->mouseMoved(x,y);

}
void GameBoard::mouseReleaseEvent(QMouseEvent * event) {
   event->accept();
   auto x = event->x() * _game->size().width() / (double)rect().width()  ;
   auto y = event->y() * _game->size().height() / (double)rect().height() ;
   _game->mouseReleased(x,y);

}
