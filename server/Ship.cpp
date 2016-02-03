#include "Ship.hh"


Ship::Ship(qint32 id)
    : Entity(id, Entity::SHIP)
{
    _speed = 21;
}

Ship::Ship(qint32 id, QRect rect, quint32 vie, qint32 shipId)
    : Entity(id, Entity::SHIP)
{
    _speed = 21;
    _rect = rect;
    _vie = vie;
    _img = QImage("images/shipAlpha.png");
    _shipId = shipId;

}
void Ship::createShipPolygon()
{
    //this->addPoint(QPoint(_rect.x(), _rect.y()));
    this->addPoint(QPoint(this->xy().x() + this->size().height(), this->xy().y()));
    this->addPoint(QPoint(this->xy().x() + this->size().height(), this->xy().y() + this->size().width()));
    this->addPoint(QPoint(this->xy().x() + this->size().height(), this->xy().y()));


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





