#include "game.h"

Game::Game(const QSize &size,QObject *parent):QObject(parent), _isRunning(false),_speed(50), _size(size){
    _timer.setSingleShot(false);
    connect(&_timer,SIGNAL(timeout()),this,SLOT(update()));
}
const QSize &Game::size() const {
    return _size;
}
void Game::start() {
    _timer.start( 100 - _speed +1);
    _isRunning = true;
}

void Game::pause(){
    _timer.stop();
    _isRunning = false;

}

void Game::reset(){
    pause();
    initialize();
    emit changed();
}
void Game::update() {
    if( _isRunning == true ) {
        step();
        emit changed();
    }
}
void Game::setSpeed( int speed ) {
    if( speed >=1 && speed <= 100) {
        _speed = speed;
        if( _isRunning == true ) {
            pause();
            start();
        }

    }
}
bool Game::isRunning() const {
    return _isRunning;
}

int Game::speed() const {
    return _speed;
}
