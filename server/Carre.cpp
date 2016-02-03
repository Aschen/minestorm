#include "Carre.hh"

Carre::Carre(qint32 id)
    : Entity(id, Entity::CARRE)
{
    _speed = 21;
}

Carre::Carre(qint32 id, const QPoint &a, qint32 size, qint32 color)
    : Entity(id, Entity::CARRE),
      _color(color)
{
    _speed = 21;

    this->addPoint(a);
    this->addPoint(QPoint(a.x() + size, a.y()));
    this->addPoint(QPoint(a.x() + size, a.y() + size));
    this->addPoint(QPoint(a.x(), a.y() + size));
}

Carre::~Carre()
{
}

qint32 Carre::color() const
{
    return _color;
}

