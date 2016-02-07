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
    if(_speed < 6)
        _speed += 3;
}

void Entity::decrementSpeed()
{
    if(_speed > 0)
        _speed -= 1;
    else
        _speed = 0;
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
        DEBUG("Entity::rotate() x':" << p.x() << " y':" << p.y(), false);
    }
}

bool Entity::makeEntityMove()
{
    if (_speed > 0)
    {
        qreal dX, dY, centreX, centreY;
        centreX = this->center().x();
        centreY = this->center().y();
        DEBUG("Entity::x:" << this->center().x() << " y:" << this->center().y(), false);

        if (centreX > SCREEN_SIZE)
        {
            dX = -SCREEN_SIZE;
            dY = 0;
        }
        else if (centreY > SCREEN_SIZE)
        {
            dX = 0;
            dY = -SCREEN_SIZE;
        }
        else if (centreY < 0)
        {
            dX = 0;
            dY = SCREEN_SIZE;
        }
        else if (centreX < 0)
        {
            dX = SCREEN_SIZE;
            dY = 0;
        }
        else {
            dX = _speed * cos(getRadian(_angle));
            dY = _speed * sin(getRadian(_angle));
        }

        _speed > 0.15 ? _speed *= 0.96 : _speed = 0;


        this->translate(dX, dY);
        DEBUG("Entity::speed:" << _speed, true);
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

qreal Entity::speed() const
{
    return _speed;
}

void Entity::speed(qreal value)
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

void Entity::setEtatDead()
{
    _etat = Etat::DEAD;
}
