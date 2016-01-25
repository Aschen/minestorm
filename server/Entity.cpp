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
    _points.push_back(point);
}

Entity::Type Entity::type() const
{
    return _type;
}

const string Entity::name() const
{
    return _name;
}

const QVector<QPoint> Entity::points() const
{
    return _points;
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
    for (int i = 0; i < _points.size(); ++i)
    {
        ret << static_cast<char>(i + 'A');
        ret << "(" << _points[i].x() << "," << _points[i].y() << ") ";
    }

    return ret.str();
}


Entity &operator<<(Entity &entity, const QPoint &point)
{
    entity.addPoint(point);

    return entity;
}

const char * const Entity::TYPE_DISPLAY[] = {"MINE",
                                             "SHIP",
                                             "SHOT"};
