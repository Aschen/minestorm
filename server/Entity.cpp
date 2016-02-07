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

void Entity::rightRotate()
{
    _angle = (_angle + 10) % 360;

    QTransform t;
    QPoint center(((*this)[0].x() + (*this)[1].x() + (*this)[2].x()) / 3,
                ((*this)[0].y() + (*this)[1].y() + (*this)[2].y()) / 3);
    t.translate(center.x(), center.y());
    t.rotate(+10);
    t.translate(center.x() * -1, center.y() * -1);
    QPolygon newP = t.map(*this);
    this->swap(newP);
}

void Entity::leftRotate()
{
    _angle = (_angle - 10) % 360;

    QTransform t;
    QPoint center(((*this)[0].x() + (*this)[1].x() + (*this)[2].x()) / 3,
                ((*this)[0].y() + (*this)[1].y() + (*this)[2].y()) / 3);
    t.translate(center.x(), center.y());
    t.rotate(-10);
    t.translate(center.x() * -1, center.y() * -1);
    QPolygon newP = t.map(*this);
    this->swap(newP);
}

void Entity::makeEntityMove()
{
    if(_speed > 0) {
        /*
        if(this->x() > SCREEN_SIZE )
            this->translate(0, _speed * sin(getRadian()));
        if(this->y() > SCREEN_SIZE )
            this->translate(_speed * cos(getRadian()), 0);

        if(this->y() < 0)
            this->translate(_speed * cos(getRadian()), SCREEN_SIZE);

        if(this->x() < 0)
            this->translate(SCREEN_SIZE, _speed * sin(getRadian()));
        */
        this->translate(_speed * cos(getRadian()), _speed * sin(getRadian()));
        DEBUG("Entity::Coord : " << x() << ";" << y(), false);
    }

}

double Entity::getRadian()
{
    return ( this->angle() * ( M_PI / 180));
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
    DEBUG("X" << y(), false);
    if(value> SCREEN_SIZE)
    {
        value = 0;
        DEBUG("X > Screen size" << x(), false);
    }
    if(value < 0)
    {
        value = SCREEN_SIZE;

        DEBUG("X < 0 : "<< x(), false);
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
    if(value - SHIP_SIZE > SCREEN_SIZE )
    {
        value =  0;
        DEBUG("Y > SCREEN SIZE"<< y(), false);
    }
    if(value  < 0)
    {
        value = SCREEN_SIZE;
        DEBUG("Y < 0"<< y(), false);
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

qint32 Entity::angle() const
{

    return _angle;
}

void Entity::angle(qint32 value)
{
    _angle = value;
}
