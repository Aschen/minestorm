#include "Ship.hh"

Ship::Ship(const QPointF &position, qint32 shipNumber)
    : Entity(Entity::SHIP),
      _vie(3),
      _shipNumber(shipNumber),
      _tempo(0),
      _score(0),
      _scoreChanged(true),
      _livesChanged(true),
      _shooting(false),
      _shield(false),
      _goingUp(false),
      _rotation(NONE),
      _shieldRepop(-1),
      _spawn(position)
{
    _size   = QSize(SHIP_SIZE, SHIP_SIZE);

    init();
    grantShield();

    this->vx(0);
    this->vy(0);
}

void Ship::addScore(quint32 score)
{
    _score += score;
    DEBUG("Ship::addScore() : add:" << score << " total:" << _score, false);

    /* Tell the Core that score has changed */
    _scoreChanged = true;
}

void Ship::init()
{
    _speed      = 0;
    _angle      = 0;
    _etat       = INVINCIBLE;
    _timerSpawn = 120;
    _vx         = 0.0;
    _vy         = 0.0;
    _shieldRepop = -1;
    _shield     = true;

    this->addPoint(QPointF(_spawn.x(), _spawn.y()));
    this->addPoint(QPointF(_spawn.x() + size().width(), _spawn.y()));
    this->addPoint(QPointF(_spawn.x() + size().height(), _spawn.y() + size().width()));
    this->addPoint(QPointF(_spawn.x(), _spawn.y() + size().height()));
}

void Ship::resetSpawn()
{
    this->clear();
    init();
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

bool Ship::haveShield() const
{
    return _shield == true ;
}

void Ship:: grantShield()
{
    DEBUG("Ship::Shield grant", false);
    _shield = true;
}

bool Ship::removeShield()
{
    DEBUG("Ship::Shield Lost", false);
    _shield = false;
    _shieldRepop = CYCLE_PER_S * SHIELD_REPOP;
    return _shield;
}

QSharedPointer<Entity> Ship::shot()
{
    return QSharedPointer<Entity>(new Projectile(*this));
}

QSharedPointer<Entity> Ship::startShooting()
{
    _shooting = true;
    return shot();
}

bool Ship::isShooting(quint32 cycle) const
{
    /* Apply shoot rate */
    return (cycle % (CYCLE_PER_S / SHOT_PER_S) == 0) && _shooting;
}

void Ship::stopShooting()
{
    _shooting = false;
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
    bool changeLife = false;

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
            this->setEtatDead();
        }
        else
        {
            resetSpawn();
        }

        changeLife = true;
        /* Tell Core that lives has changed */
        _livesChanged = true;
    }

    return changeLife;
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
    if (_timerSpawn > 0)
    {
        _timerSpawn--;
        if (_timerSpawn == 0)
            _etat = ALIVE;
    }
    rotateShip();
    qreal tempX, tempY;

    /* Repop shield */
    if (_shieldRepop == 0)
    {
        grantShield();
    }
    _shieldRepop--;

    if (goingUp())
    {
        tempX = vx() + (_speed / 2) * cos(getRadian(_angle));
        tempY = vy() + (_speed / 2) * sin(getRadian(_angle));

        if (tempX > 10)
          tempX = 10;
       else if (tempX < -10)
           tempX = -10;

        if (tempY > 10)
            tempY = 10;
        else if (tempY < -10)
            tempY = -10;

        this->vy(tempY);
        this->vx(tempX);
    }
    else
    {
        if(vx() > 0.3 || vx() < -0.3)
            vx(vx() * 0.97);
        else {
            vx(0);
        }

        if(vy() > 0.3 || vy() < -0.3)
            vy(vy() * 0.97);
        else
        {
            vy(0);
        }
    }
    Entity::makeEntityMove();
    return true;
}
