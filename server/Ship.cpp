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
    DEBUG("Ship::angle:" << _angle, true);
    rightRotate();
    this->createShipPolygon();
    DEBUG("Ship::angle:" << _angle, true);
}

void Ship::rotateShipLeft()
{
    DEBUG("Ship::anglex:" << this->x(), true);
    leftRotate();
    this->createShipPolygon();
    DEBUG("Ship::anglex:" << this->x(), true);
}

double Ship::getRadian()
{
    return ( this->angle() * ( PI / 180));
}





