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
    DEBUG("Entity::speed+++: "<< _speed, true);
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
    _angle += angle;
    QPoint entityCenter = center();
    double angleRad = getRadian(angle);
    qint32 x,y;
    for(QPoint &p : *this)
    {
        x = (cos(angleRad) * (p.x() - entityCenter.x()) - sin(angleRad) * (p.y() - entityCenter.y()) + entityCenter.x());
        y = (sin(angleRad) * (p.x() - entityCenter.x()) + cos(angleRad) * (p.y() - entityCenter.y()) + entityCenter.y());
        p.setX(x);
        p.setY(y);
    }
}

bool Entity::makeEntityMove()
{
    if(_speed > 0) {
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
