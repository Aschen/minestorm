#include "Projectile.hh"

Projectile::Projectile(qint32 id, Ship& ship)
    : Entity(id, Entity::SHOT), _ship(ship)
{
    this->setId(id);
    this->speed(20);
    this->angle(_ship.angle());

    init();
}

void Projectile::init()
{
    QPointF a = _ship.center();
    QPointF b = QPointF(a.x() + 6 * cos(_ship.getRadian(0)),
                      a.y() + 6 * sin(_ship.getRadian(0)));

    this->addPoint(a);
    this->addPoint(b);

    DEBUG("A(" << a.x() << "," << a.y() << ") - B(" << b.x() << "," << b.y() << ")", false);
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
    qreal  x;
    qreal  y;

    x = ((*this)[0].x() + (*this)[1].x()) / 2;
    y = ((*this)[0].y() + (*this)[1].y()) / 2;
    DEBUG("Projectile::center() : 2 points :" << x << y, false);
    return QPointF(x, y);
}

bool Projectile::makeEntityMove()
{/*
    if(_etat == Entity::ALIVE)
    {
        this->translate(_speed * cos(getRadian()), _speed * sin(getRadian()));
    }*/
    return true;
}
