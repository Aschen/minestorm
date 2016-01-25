#include "game.h"

Game::Game(const QSize &size, QObject *parent)
    : QObject(parent), _isRunning(false), _size(size)
{
    _timer.setSingleShot(false);
    // Le signal timeout() est envoyé toutes les 40ms, on le connecte à la fonction Game::update()
    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
}

const QSize &Game::size() const
{
    return _size;
}

void Game::start()
{
    _timer.start(40); // Répète le timer toutes les 40ms (25 fps)
    _isRunning = true;
}

void Game::pause()
{
    _timer.stop();
    _isRunning = false;
}

void Game::reset()
{
    pause();
    initialize();
    emit changed();
}

void Game::update()
{
    if( _isRunning == true )
    {
        emit changed();
    }
}

bool Game::isRunning() const
{
    return _isRunning;
}
