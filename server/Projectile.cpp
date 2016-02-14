#include "Projectile.hh"

Projectile::Projectile(Ship& ship)
    : Entity(Entity::SHOT), _ship(ship)
{
    this->speed(40);
    this->angle(_ship.angle());
    init();

    DEBUG("Tir:angle:"<<_angle << ", speed" <<_speed <<", pos" << this->center().x() <<":"<<this->center().y(), false);

}

void Projectile::init()
{
    QPointF a =  QPointF(_ship.center().x() + 16 * cos(_ship.getRadian(_angle)),
                         _ship.center().y() + 16 * sin(_ship.getRadian(_angle)));
    QPointF b = QPointF(a.x() + 6 * cos(_ship.getRadian(_angle)),
                      a.y() + 6 * sin(_ship.getRadian(_angle)));

    this->addPoint(a);
    this->addPoint(b);

    DEBUG("A(" << a.x() << "," << a.y() << ") - B(" << b.x() << "," << b.y() << ")", false);
}

Ship &Projectile::ship() const
{
    return _ship;
}

QPointF Projectile::center() const
{
    qint32  x;
    qint32  y;

    x = ((*this)[0].x() + (*this)[1].x()) / 2;
    y = ((*this)[0].y() + (*this)[1].y()) / 2;
    DEBUG("Projectile::center() : 2 points :" << x << y, false);
    return QPointF(x, y);
}

bool Projectile::makeEntityMove()
{
    bool    ret = false;

    if(_etat == Entity::ALIVE)
    {
        if (this->center().x() > SCREEN_WIDTH
        ||  this->center().y() > SCREEN_HEIGHT
        ||  this->center().y() < 0
        ||  this->center().x() < 0)
        {
            this->setEtatDead();
            ret = false;
        }
        else
        {
            this->translate(_speed * cos(getRadian(_angle)), _speed * sin(getRadian(_angle)));
            ret =  true;
        }
    }

    return ret;
}
