#include "Entity.hh"

Entity::Entity(qint32 id, Type type)
    : _type(type),
      _id(id)
{
    _etat = ALIVE;
}

Entity::~Entity()
{
}

void Entity::addPoint(const QPoint &point)
{
    *this << point;
}

bool Entity::isMoving()
{
    return _speed > 0;
}

void Entity::incrementSpeed()
{
    if(_speed < 10)
        ++_speed;
}

void Entity::decrementSpeed()
{
    if(_speed > 0)
        --_speed;
}

void Entity::rightRotate()
{
    _angle -= 10;

    QTransform t;
    t.rotate(_angle);
    QPolygon newPolygon = t.map(*this);
    this->swap(newPolygon);
}

void Entity::leftRotate()
{
    _angle += 10;

    QTransform t;
    t.rotate(_angle);
    QPolygon newPolygon = t.map(*this);
    this->swap(newPolygon);
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

void Entity::x(qint32 value)
{
    DEBUG("X:" << x(), false);
    if(value > SCREEN_SIZE - SHIP_SIZE)  {
        value *= -1;
        DEBUG("ENtity : X > SCREEN SIZE", false);
    }
    if(value < 0 + SHIP_SIZE) {
        value *= -1;
        DEBUG("ENtity : X < SCREEN SIZE", false);
    }
    _xy = QPoint(value, y());
}

qint32 Entity::y() const
{
    return _xy.y();
}

void Entity::y(qint32 value)
{

    DEBUG("Y" << y(), false);
    if(value > SCREEN_SIZE - SHIP_SIZE)  {
        value *= -1;
        DEBUG("ENtity : Y > SCREEN SIZE", false);
    }
    if(value < 0 + SHIP_SIZE) {
        value *= -1;
        DEBUG("ENtity : Y < SCREEN SIZE", false);
    }

    _xy = QPoint(x(), value);
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
