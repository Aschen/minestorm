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

void Entity::addPoint(const qreal x, const qreal y)
{
    QPointF point(x,y);
    *this << point;
}

bool Entity::isMoving()
{
    return _speed > 0;
}

void Entity::incrementSpeed()
{
    DEBUG("Entity::speed++: "<< _speed, false);

    if (_speed < 20)
        _speed += 5;
    else
        _speed = 20;
}

void Entity::decrementSpeed(qint32 value)
{
    if (_speed > value)
        _speed -= value;
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
        DEBUG("Entity::rotate() x:" << p.x() << " y:" << p.y(), false);
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
        qreal centreX, centreY;
        centreX = this->center().x();
        centreY = this->center().y();
        DEBUG("Entity::x:" << this->center().x() << " y:" << this->center().y(), false);

        if (centreX > SCREEN_SIZE)
        {
            this->translate(-SCREEN_SIZE, 0);
        }
        else if (centreX < 0)
        {
            this->translate(SCREEN_SIZE, 0);
        }
        else if (centreY > SCREEN_SIZE)
        {
            this->translate(0, -SCREEN_SIZE);
        }
        else if (centreY < 0)
        {
            this->translate(0, SCREEN_SIZE);
        }
        else {
            this->translate(_speed / 2 * cos(getRadian(_angle)),
                            _speed / 2 * sin(getRadian(_angle)));

            DEBUG("Entity::angle:" << this->center().x(), false);
        }

        if(_temporisation % 10 == 0)
            decrementSpeed(1);
        DEBUG("Entity::speed:" << _speed, false);

        _temporisation = ( _temporisation + 1 ) % 100;
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

Entity::Etat Entity::etat() const
{
    return _etat;
}

void Entity::setEtatDead()
{
    _etat = Etat::DEAD;
}

bool Entity::isDead()
{
    return _etat == Etat::DEAD;
}
