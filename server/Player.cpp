#include "Player.hh"

Player::Player(quint32 number, const QPoint &spawn)
    : _number(number),
      _spawn(spawn),
      _available(true)
{
}

Player::Player()
{
}

QSharedPointer<Entity> &Player::newPlayer(qint32 idClient)
{
    DEBUG("Player::newPlayer() idClient:" << idClient, true);

    _ship = QSharedPointer<Entity>(new Ship(idClient, _spawn, _number));
    _idClient = idClient;
    _available = false;

    return _ship;
}

void Player::playerLeft()
{
    DEBUG("Player::playerLeft() idClient:" << _idClient, true);
    _ship = QSharedPointer<Entity>();
    _idClient = 0;
    _available = true;
}

Ship &Player::ship()
{
    return *dynamic_cast<Ship*>(_ship.data());
}

quint32 Player::number() const
{
    return _number;
}

const QPoint &Player::spawn() const
{
    return _spawn;
}

bool Player::available() const
{
    return _available;
}

qint32 Player::idClient() const
{
    return _idClient;
}

quint32 Player::score() const
{
    if (!_available)
        return dynamic_cast<Ship*>(_ship.data())->score();
    return 42424242;
}

quint32 Player::lives() const
{
    if (!_available)
        return dynamic_cast<Ship*>(_ship.data())->vie();
    return 42424242;
}
