#include "Projectile.hh"

Projectile::Projectile(qint32 id, Ship& ship)
    : Entity(id, Entity::SHOT), _ship(ship)
{
    this->setId(id);

    init();
}

void Projectile::init()
{
    QPoint a = _ship.xy();
    QPoint b = QPoint(_ship.x() + 6 * cos(_ship.getRadian()),
                      _ship.y() + 6 * sin(_ship.getRadian()));

    this->addPoint(a);
    this->addPoint(b);
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

QPoint Projectile::center() const
{
    qint32  x;
    qint32  y;

    x = ((*this)[0].x() + (*this)[1].x()) / 2;
    y = ((*this)[0].y() + (*this)[1].y()) / 2;
    DEBUG("Projectile::center() : 2 points :" << x << y, false);
    return QPoint(x, y);
}
