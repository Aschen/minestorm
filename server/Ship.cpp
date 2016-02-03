#include "Ship.hh"


Ship::Ship(string name)
    : Entity(name, Entity::SHIP)
{
    _speed = 21;
}

Ship::Ship(qint32 name, QRect rect, int vie)
    : Entity(name, Entity::SHIP)
{
    _speed = 21;
    _rect = rect;
    _vie = vie;
    _img = QImage("images/shipAlpha.png");


}
void Ship::drawShip()
{
    //this->addPoint(QPoint(_rect.x(), _rect.y()));
    this->addPoint(QPoint(_rect.x() + _rect.height(), _rect.y()));
    this->addPoint(QPoint(_rect.x()+ _rect.height(), _rect.y() + _rect.width()));
    this->addPoint(QPoint(_rect.x(), _rect.y() + _rect.width()));

}

//Getter & Setter
int Ship::vie() const
{
    return _vie;
}

void Ship::setVie(int vie)
{
    _vie = vie;
}
QRect Ship::rect() const
{
    return _rect;
}

void Ship::setRect(const QSize &rect)
{
    _rect = rect;
}
QImage Ship::img() const
{
    return _img;
}

void Ship::setImg(const QImage &img)
{
    _img = img;
}





