#include "Ship.hh"


Ship::Ship(qint32 id, const QPoint &position, qint32 shipNumber)
    : Entity(id, Entity::SHIP),
      _vie(3),
      _shipNumber(shipNumber)
{
    _size   = QSize(SHIP_SIZE, SHIP_SIZE);
    _speed  = 0;
    _angle  = 0;

    this->addPoint(QPoint(position.x(), position.y()));
    this->addPoint(QPoint(position.x() + size().width(), position.y()));
    this->addPoint(QPoint(position.x() + size().height(), position.y() + size().width()));
    this->addPoint(QPoint(position.x(), position.y() + size().height()));
}


//Getter & Setter
quint32 Ship::vie() const
{
    return _vie;
}


void Ship::setVie(quint32 vie)
{
    _vie = vie;
}

quint32 Ship::shipNumber() const
{
    return _shipNumber;
}

void Ship::shipNumber(quint32 shipNumber)
{
    _shipNumber = shipNumber;
}


double Ship::getRadian()
{
    return ( this->angle() * ( PI / 180));
}

QPoint Ship::center() const
{
    qint32  x;
    qint32  y;

    x = ((*this)[0].x() + (*this)[1].x() + (*this)[2].x() + (*this)[3].y())  / 4;
    y = ((*this)[0].y() + (*this)[1].y() + (*this)[2].y() + (*this)[3].y() ) / 4;
    DEBUG("Ship::center() : 4 points :" << x << y, true);
    return QPoint(x, y);
}

bool Ship::changeLife(qint32 change)
{
    bool aliveOrNot = true;
    _vie += change;
    if(_vie == 0)
    {
        aliveOrNot = false;
    }
    return aliveOrNot;
}
