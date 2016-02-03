#include "Carre.hh"

Carre::Carre(qint32 id)
    : Entity(id, Entity::CARRE)
{
    _speed = 21;
}

Carre::Carre(qint32 id, const QPoint &a, qint32 size)
    : Entity(id, Entity::CARRE)
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

