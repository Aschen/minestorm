#include "Entity.hh"

Entity::Entity(string name, Type type)
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

const string Entity::name() const
{
    return _name;
}

int Entity::speed() const
{
    return _speed;
}

void Entity::speed(int value)
{
    _speed = value;
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
