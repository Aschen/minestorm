#include "Entity.hh"



Etat Entity::etat() const
{
    return _etat;
}

void Entity::setEtat(const Etat &etat)
{
    _etat = etat;
}
Entity::Entity(qint32 id, Type type)
    : _type(type),
      _id(id)
{
    _etat = ALIVE;
}

Entity::~Entity()
{
}

void Entity::addPoint(const QPointF &point)
{
    *this << point;
}

bool Entity::isMoving()
{
    return _speed > 0;
}

void Entity::incrementSpeed()
{
    DEBUG("Entity::speed++: "<< _speed, true);
    if(_speed < 10)
        ++_speed;
}

void Entity::decrementSpeed()
{
    if(_speed > 0)
        --_speed;
}

void Entity::rotate(qint32 angle)
{
    _angle = (_angle + angle) % 360;

    qreal      cx = center().x();
    qreal      cy = center().y();
    qreal      x;
    qreal      y;
    qreal      theta = getRadian(angle);

    for (QPointF &p : *this)
    {
        DEBUG("Entity::rotate() x:" << p.x() << " y:" << p.y(), true);
        x = cos(theta) * (p.x() - cx) - sin(theta) * (p.y() - cy) + cx;
        y = sin(theta) * (p.x() - cx) + cos(theta) * (p.y() - cy) + cy;
        p.setX(x);
        p.setY(y);
        DEBUG("Entity::rotate() x':" << p.x() << " y':" << p.y(), true);
    }
}

bool Entity::makeEntityMove()
{
    if(_speed > 0)
    {
        /*
        if(this->x() > SCREEN_SIZE )
            this->translate(0, _speed * sin(gestRadian()));
        if(this->y() > SCREEN_SIZE )
            this->translate(_speed * cos(getRadian()), 0);

        if(this->y() < 0)
            this->translate(_speed * cos(getRadian()), SCREEN_SIZE);

        if(this->x() < 0)
            this->translate(SCREEN_SIZE, _speed * sin(getRadian()));
        */
        this->translate(_speed * cos(getRadian(_angle)), _speed * sin(getRadian(_angle)));
    }
    return true;
}

double Entity::getRadian(qint32 angle)
{
    return ( angle * ( M_PI / 180));
}

Entity::Type Entity::type() const
{
    return _type;
}

qint32 Entity::id() const
{
    return _id;
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

qint32 Entity::angle() const
{

    return _angle;
}

void Entity::angle(qint32 value)
{
    _angle = value;
}
