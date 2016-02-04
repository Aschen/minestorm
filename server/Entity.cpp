#include "Entity.hh"

Entity::Entity(qint32 id, Type type)
    : _type(type),
      _id(id)
{
}

Entity::~Entity()
{
}

void Entity::addPoint(const QPoint &point)
{
    *this << point;
}

Entity::Type Entity::type() const
{
    return _type;
}

qint32 Entity::id() const
{
    return _id;
}

const QPoint &Entity::xy() const
{
    return _xy;
}

void Entity::xy(const QPoint &value)
{
    _xy = value;
}

qint32 Entity::x() const
{
    return _xy.x();
}

qint32 Entity::y() const
{
    return _xy.y();
}

const QSize &Entity::size() const
{
    return _size;
}

void Entity::size(const QSize &value)
{
    _size = value;
}

qint32 Entity::speed() const
{
    return _speed;
}

void Entity::speed(qint32 value)
{

    _speed = value;
}

double Entity::angle() const
{

    return _angle;
}

void Entity::angle(double value)
{
    _angle = value;
}
