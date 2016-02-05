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
                      _ship.y() + 6 * sin(_ship.getRadian())
                      );

    this->_line = QLine(a, b);

    //DEBUG("x = " << b.x(), true);
    //DEBUG("y = " << b.y(), true);
}

QLine Projectile::line() const
{
    return _line;
}

void Projectile::setLine(const QLine &line)
{
    _line = line;
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

void Projectile::setShip(Ship const &ship)
{
    //_ship = ship;
}





