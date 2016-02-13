#include "Player.hh"

Player::Player(qint32 idClient, quint32 number, const QPoint &spawn)
    : _idClient(idClient),
      _number(number),
      _spawn(spawn)
{
    DEBUG("Player::Player() idClient:" << _idClient << " number:" << _number, true);
    _ship = QSharedPointer<Entity>(new Ship(_spawn, _number));
}

Player::~Player()
{
    /* Set Ship as dead so Core can clean it from Ship list*/
    this->ship().setEtatDead();
}



QSharedPointer<Entity> &Player::entity()
{
    return _ship;
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

qint32 Player::idClient() const
{
    return _idClient;
}

quint32 Player::score() const
{
    return dynamic_cast<Ship*>(_ship.data())->score();
}

quint32 Player::lives() const
{
    return dynamic_cast<Ship*>(_ship.data())->vie();
}
