#include "Entity.hh"

Entity::Entity(Type type)
    : _type(type),
      _angle(0)
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

    if (_speed < 10)
        _speed += 1;
    else
        _speed = 10;
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
        DEBUG("Entity::makeEntityMove() x:" << this->center().x() << " y:" << this->center().y(), false);
        if (centreX > SCREEN_WIDTH)
        {
            this->translate(-SCREEN_WIDTH, 0);
        }
        else if (centreX < 0)
        {
            this->translate(SCREEN_WIDTH, 0);
        }
        else if (centreY > SCREEN_HEIGHT)
        {
            this->translate(0, -SCREEN_HEIGHT);
        }
        else if (centreY < 0)
        {
            this->translate(0, SCREEN_HEIGHT);
        }
        else {
            this->translate(vx(),vy());
            DEBUG("Entity::makeEntityMove() angle:" << this->center().x(), false);
        }
        DEBUG("Entity::makeEntityMove() speed:" << _speed, false);
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

void Entity::type(Entity::Type type)
{
    _type = type;
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

Entity::Etat Entity::etat() const
{
    return _etat;
}


qreal Entity::vy() const
{
    return _vy;
}

void Entity::vy(qreal vy)
{
    _vy = vy;
    DEBUG("Entity::vy:" << _vy, false);
}
qreal Entity::vx() const
{
    return _vx;
}

void Entity::vx(qreal vx)
{
    _vx = vx;
    DEBUG("Entity::vx:" << _vx, false);
}

void Entity::setEtatDead()
{
    _etat = Etat::DEAD;
}

bool Entity::isDead()
{
    return _etat == Etat::DEAD;
}
