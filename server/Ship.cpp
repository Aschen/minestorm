#include "Ship.hh"

Ship::Ship(const QPointF &position, qint32 shipNumber)
    : Entity(Entity::SHIP),
      _vie(3),
      _shipNumber(shipNumber),
      _tempo(0),
      _score(0),
      _scoreChanged(true),
      _livesChanged(true)
{
    _size   = QSize(SHIP_SIZE, SHIP_SIZE);
    _speed  = 0;
    _angle  = 0;
    _rotation = NONE;
    _goingUp = false;

    grantShield();
    this->addPoint(QPointF(position.x(), position.y()));
    this->addPoint(QPointF(position.x() + size().width(), position.y()));
    this->addPoint(QPointF(position.x() + size().height(), position.y() + size().width()));
    this->addPoint(QPointF(position.x(), position.y() + size().height()));
}

void Ship::addScore(quint32 score)
{
    _score += score;
    DEBUG("Ship::addScore() : add:" << score << " total:" << _score, true);

    /* Tell the Core that score has changed */
    _scoreChanged = true;
}


//Getter & Setter
quint32 Ship::vie() const
{
    return _vie;
}

void Ship::setVie(quint32 vie)
{
    _vie = vie;
    _livesChanged = true;
}

quint32 Ship::shipNumber() const
{
    return _shipNumber;
}

void Ship::shipNumber(quint32 shipNumber)
{
    _shipNumber = shipNumber;
}

void Ship::score(quint32 score)
{
    _score = score;
    _scoreChanged = true;
}

quint32 Ship::score() const
{
    return _score;
}

bool Ship::scoreChanged()
{
    bool    ret = _scoreChanged;

    _scoreChanged = false;
    return ret;
}

bool Ship::livesChanged()
{
    bool    ret = _livesChanged;

    _livesChanged = false;
    return ret;
}

bool Ship::haveShield()
{
    return _shield == true ;
}

void Ship::grantShield()
{
    _shield = true;
}

bool Ship::removeShield()
{
    DEBUG("Ship::Shield Lost", false);
    _shield = false;
    return _shield;
}

QSharedPointer<Entity> Ship::shot()
{
    return QSharedPointer<Entity>(new Projectile(*this));
}

Ship::Rotation Ship::rotation() const
{
    return _rotation;
}

void Ship::setRotation(Rotation rotation)
{
    _rotation = rotation;
}

bool Ship::goingUp()
{
    return _goingUp;
}

void Ship::goingUp(bool value)
{
    _goingUp = value;
}

QPointF Ship::center() const
{
    qint32  x;
    qint32  y;

    x = ((*this)[0].x() + (*this)[1].x() + (*this)[2].x() + (*this)[3].x()) / 4;
    y = ((*this)[0].y() + (*this)[1].y() + (*this)[2].y() + (*this)[3].y()) / 4;
    DEBUG("Ship::center() : " << x << y, false);

    return QPointF(x, y);
}

bool Ship::changeLife(qint32 change)
{
    bool aliveOrNot = true;

    //On enléve une vie au vaisseau si il n'a pas de shield
    if (this->haveShield())
    {
        this->removeShield();
    }
    else
    {
        _vie += change;
        if(_vie <= 0)
        {
            aliveOrNot = false;
            this->setEtatDead();
        }

        /* Tell Core that lives has changed */
        _livesChanged = true;
    }

    return aliveOrNot;
}

void Ship::rotateShip()
{
    switch(_rotation)
    {
        case LEFT:
            this->rotate(-10);
            break;

        case RIGHT:
            this->rotate(10);
            break;
        default:
            break;
    }
}

bool Ship::makeEntityMove()
{
    rotateShip();
    if(goingUp())
        this->incrementSpeed();

    Entity::makeEntityMove();
    if(_tempo % 10 == 0)
         decrementSpeed(1);
    _tempo = ( _tempo + 1 ) % 100;
    return true;
}
