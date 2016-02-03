#include "Ship.hh"


Ship::Ship(qint32 id)
    : Entity(id, Entity::SHIP)
{
    _speed = 0;
}

Ship::Ship(qint32 id, QRect rect, quint32 vie, qint32 shipId)
    : Entity(id, Entity::SHIP)
{
    _speed = 0;
    _rect = rect;
    _vie = vie;
    _img = QImage("images/shipAlpha.png");
    _shipId = shipId;

}
void Ship::createShipPolygon()
{
    this->clear();

    this->addPoint(QPoint(this->xy().x() + this->size().height(), this->xy().y()));
    this->addPoint(QPoint(this->xy().x() + this->size().height(), this->xy().y() + this->size().width()));
    this->addPoint(QPoint(this->xy().x() + this->size().height() /2, this->xy().y() + this->size().width() / 2));
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

qint32 Ship::shipId() const
{
    return _shipId;
}

void Ship::moveShipForward()
{
    DEBUG("Ship::Coord : Client" << this->xy().x() << ";" << this->xy().y(), false);
    _speed++;
    this->xy(QPoint(
                 this->xy().x() + _speed * cos(getRadian()),
                 this->xy().y() + _speed * sin(getRadian())
                 ));
    /*
    this->xy(
            QPoint(
                 this->xy().y() * sin( getRadian() - this->xy().x() * cos(getRadian())),
                 this->xy().y() * cos( getRadian() + this->xy().x() * sin(getRadian()))
            )
    );
*/
    this->createShipPolygon();

    DEBUG("Ship::Coord : Client" << this->xy().x() << ";" << this->xy().y(), false);
}

void Ship::rotateShipRight()
{
    this->angle(this->angle() + 1);
    this->createShipPolygon();
}

void Ship::slowDownShip()
{
    _speed--;
}

void Ship::rotateShipLeft()
{
    this->angle(this->angle() - 1);
    this->createShipPolygon();
}

double Ship::getRadian()
{
    return this->angle() / 180 * PI;
}





