#include "Entity.hh"

Entity::Entity(QString name, Type type)
    : _type(type),
      _name(name)
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

const QString Entity::name() const
{
    return _name;
}

QPoint Entity::xy()
{
    return _xy;
}

void Entity::xy(QPoint value)
{
    _xy = value;
}

QSize Entity::size()
{
    return _size;
}

void Entity::size(QSize value)
{
    _size = value;
}

int Entity::speed()
{
    return _speed;
}

void Entity::speed(int value)
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

    ret << TYPE_DISPLAY[_type] << " - " << _name << " : ";
    for (int i = 0; i < this->size(); ++i)
    {
        ret << static_cast<char>(i + 'A');
        ret << "(" << this->operator[](i).x() << "," <<this->operator[](i).y() << ") ";
    }

    return ret.str();
}

const char * const Entity::TYPE_DISPLAY[] = {"MINE",
                                             "SHIP",
                                             "SHOT",
                                             "CARRE"};
