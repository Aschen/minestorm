#include "Mine.hh"

Mine::Mine(qint32 id, TypeMine typeMine, const QPointF &point)
    : Entity(id, Entity::MINE),
      _typeMine(typeMine),
      _armed(false),
      _timer(*this)
{
    switch(_typeMine)
    {
        case Small:
        case Small_On:
            _size = 10;
            _speed = 4;
            break;
        case Medium:
        case Medium_On:
            _size = 20;
            _speed = 3;
            break;
        case Big:
        case Big_On:
            _size = 30;
            _speed = 2;
            break;
    }

    addPoint(point);
    addPoint(point.x()+ _size, point.y());
    addPoint(point.x()+ _size, point.y() + _size);
    addPoint(point.x(), point.y() + _size);
}

Mine::~Mine()
{
}

void Mine::activate()
{
    DEBUG("Mine::activate() id:" << _id << " type:" << _typeMine, true);
    _armed = true;
    switch (_typeMine)
    {
    case Small:
        _typeMine = Small_On;
        break;
    case Medium:
        _typeMine = Medium_On;
        break;
    case Big:
        _typeMine = Big_On;
        break;
    default:
        break;
    }
    DEBUG("Mine::activate() type:" << _typeMine, true);
}

qint32 Mine::size() const
{
    return _size;
}

void Mine::setSize(qint32 size)
{
    _size = size;
}

Mine::TypeMine Mine::typeMine() const
{
    return _typeMine;
}

bool Mine::armed() const
{
    return _armed;
}

QPointF Mine::center() const
{
    qint32  x;
    qint32  y;

    x = ((*this)[0].x() + (*this)[1].x() + (*this)[2].x() + (*this)[3].x()) / 4;
    y = ((*this)[0].y() + (*this)[1].y() + (*this)[2].y() + (*this)[3].y()) / 4;
    return QPoint(x, y);
}
