#include "Player.hh"

Player::Player(qint32 idClient, quint32 number, const QPoint &spawn)
    : QObject(),
      _idClient(idClient),
      _number(number),
      _spawn(spawn),
      _ship(QSharedPointer<Entity>(new Ship(_spawn, _number))),
      _acceptShot(true)
{
    DEBUG("Player::Player() idClient:" << _idClient << " number:" << _number, true);
    /* Prepare timer to limit shot rate */
    connect(&_shotTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    connect(this, SIGNAL(stopTimer()), &_shotTimer, SLOT(stop()));
}

Player::~Player()
{
    /* Set Ship as dead so Core can clean it from Ship list*/
    this->ship().setEtatDead();
}

void Player::startShooting(EntityList *shots)
{
    _shots = shots;

    _shotTimer.start(1000 / SHOT_PER_S);
}

void Player::stopShooting()
{
    emit stopTimer();
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

void Player::shoot()
{
    _shots->push_back (QSharedPointer<Entity>(new Projectile(this->ship())));
}
