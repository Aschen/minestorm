#include "Ship.hh"


Ship::Ship(qint32 id, QPoint position)
    : Entity(id, Entity::SHIP)
{
    _size   = QSize(SHIP_SIZE, SHIP_SIZE);
    _img    = QImage("images/shipAlpha.png");
    _xy     = position;
    _speed  = 0;
    _vie    = 3;
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
QRect Ship::rect() const
{
    return _rect;
}

void Ship::setRect(const QRect &rect)
{
    _rect = rect;
}
QImage Ship::img() const
{
    return _img;
}

void Ship::setImage(const QImage &img)
{
    _img = img;
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





