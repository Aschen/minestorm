#include "Ship.hh"


Ship::Ship(qint32 id, const QPoint &position, qint32 shipNumber)
    : Entity(id, Entity::SHIP),
      _vie(3),
      _shipNumber(shipNumber)
{
    _size   = QSize(SHIP_SIZE, SHIP_SIZE);
    _xy     = position;
    _speed  = 0;
}

void Ship::createShipPolygon()
{
    this->clear();
    this->addPoint(QPoint(x() + size().height(), y()));
    this->addPoint(QPoint(x() + size().height(), y() + size().width()));
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

void Ship::moveShipForward()
{
    DEBUG("Ship::Coord : Client" << this->xy().x() << ";" << this->xy().y(), false);


    x(x() + _speed * cos(getRadian()));
    y(y() + _speed * sin(getRadian()));

    createShipPolygon();

    DEBUG("Ship::speed:" << _speed, false);
    DEBUG("Ship::Coord : Client" << this->xy().x() << ";" << this->xy().y(), false);
}

void Ship::rotateShipRight()
{
    DEBUG("Ship::angle:" << _angle, false);
    rightRotate();
    this->createShipPolygon();
    DEBUG("Ship::angle:" << _angle, false);
}

void Ship::rotateShipLeft()
{
    DEBUG("Ship::anglex:" << this->x(), false);
    leftRotate();
    this->createShipPolygon();
    DEBUG("Ship::anglex:" << this->x(), false);
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
