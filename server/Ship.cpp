#include "Ship.hh"


Ship::Ship(qint32 id, const QPoint &position, qint32 shipNumber)
    : Entity(id, Entity::SHIP),
      _vie(3),
      _shipNumber(shipNumber)
{
    _size   = QSize(SHIP_SIZE, SHIP_SIZE);
    _xy     = position;
    _speed  = 0;
    _angle  = 0;

    this->addPoint(QPoint(position.x() + size().height(), position.y() + size().width()));
    this->addPoint(QPoint(position.x() + size().height(), position.y()));
    this->addPoint(QPoint(position.x() + size().height() /2, position.y() + size().width() / 2));
}

void Ship::createShipPolygon()
{
    this->clear();
    this->addPoint(QPoint(x() + size().height(), y() + size().width()));
    this->addPoint(QPoint(x() + size().height(), y()));
    this->addPoint(QPoint(x() + size().height() /2, y() + size().width() / 2));
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

void Ship::rotateShipRight()
{
    DEBUG("Right::angle:" << _angle, true);
    rightRotate();
    DEBUG("Right::angle:" << _angle, true);
}

void Ship::rotateShipLeft()
{
    DEBUG("Left::angle:" << _angle, true);
    leftRotate();
    DEBUG("Left::angle:" << _angle, true);
}

double Ship::getRadian()
{
    return ( this->angle() * ( PI / 180));
}

QPoint Ship::center() const
{
    qint32  x;
    qint32  y;

    x = ((*this)[0].x() + (*this)[1].x() + (*this)[2].x()) / 3;
    y = ((*this)[0].y() + (*this)[1].y() + (*this)[2].y()) / 3;
    DEBUG("Ship::center() : 3 points :" << x << y, false);
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
