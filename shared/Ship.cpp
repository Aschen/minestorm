#include "Ship.hh"

Ship::Ship()
{
}

Ship::Ship(QRect rect, int vie)
{
    _rect = rect;
    _vie = vie;
    _img = QImage("images/shipAlpha.png");
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

void Ship::setRect(const QRect &rect)
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





