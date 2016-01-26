#include "Carre.hh"

Carre::Carre(string name)
    : Entity(name, Entity::CARRE)
{
    _speed = 21;
}

Carre::Carre(string name, const QPoint &a, int size)
    : Entity(name, Entity::CARRE)
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

