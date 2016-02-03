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

QSize Entity::size() const
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

const std::string Entity::dump() const
{
    std::stringstream     ret;

//    ret << TYPE_DISPLAY[_type] << " - " << _id << " : ";
//    for (int i = 0; i < this->size(); ++i)
//    {
//        ret << static_cast<char>(i + 'A');
//        ret << "(" << this->operator[](i).x() << "," <<this->operator[](i).y() << ") ";
//    }

    return ret.str();
}

const char * const Entity::TYPE_DISPLAY[] = {"MINE",
                                             "SHIP",
                                             "SHOT",
                                             "CARRE"};
