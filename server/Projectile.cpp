#include "Projectile.hh"

Projectile::Projectile(qint32 id, Ship& ship)
    : Entity(id, Entity::SHOT), _ship(ship)
{
    this->setId(id);
    this->speed(20);
    this->angle(_ship.angle());
    init();

    DEBUG("Tir:angle:"<<_angle << ", speed" <<_speed <<", pos" << this->center().x() <<":"<<this->center().y(), true);

}

void Projectile::init()
{
    QPointF a = _ship.center();
    QPointF b = QPointF(a.x() + 6 * cos(_ship.getRadian(_angle)),
                      a.y() + 6 * sin(_ship.getRadian(_angle)));

    this->addPoint(a);
    this->addPoint(b);

    DEBUG("A(" << a.x() << "," << a.y() << ") - B(" << b.x() << "," << b.y() << ")", true);
}

qint32 Projectile::id() const
{
    return _id;
}

void Projectile::setId(const qint32 &id)
{
    _id = id;
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
    DEBUG("Projectile::center() : 2 points :" << x << y, true);
    return QPointF(x, y);
}

bool Projectile::makeEntityMove()
{
    if(_etat == Entity::ALIVE)
    {
        if (this->center().x() > SCREEN_SIZE
        ||  this->center().y() > SCREEN_SIZE
        ||  this->center().y() < 0
        ||  this->center().x() < 0)
        {
            this->setEtatDead();
            return false;
        }
        else
        {
            this->translate(_speed * cos(getRadian(_angle)), _speed * sin(getRadian(_angle)));
            return true;
        }
    }
}
