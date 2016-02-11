#include "Mine.hh"

Mine::Mine(qint32 id, TypeMine type, QPointF point, QTime birthDate) : Entity(id, Entity::MINE)
{
    this->setType(type);
    this->angle(rand() % 360);
    this->setBirthDate(birthDate);
    this->setBrushStyle(Qt::SolidPattern);
    this->_id = id;

    switch(type)
    {
        case Small:
            setSize(10);
            setColor(*new QColor(Qt::blue));
            this->speed(3);
            break;
        case Medium:
            setSize(20);
            setColor(*new QColor(Qt::yellow));
            this->speed(2);
            break;
        case Big:
            setSize(30);
            setColor(*new QColor(Qt::red));
            this->speed(1);
    }

    createPolygon(point);
}

void Mine::createPolygon(QPointF point)
{
    this->addPoint(point);
    this->addPoint(point.x()+ this->size(), point.y());
    this->addPoint(point.x()+ this->size(), point.y() + this->size());
    this->addPoint(point.x(), point.y() + this->size());
}

int Mine::size() const
{
    return _size;
}

void Mine::setSize(int size)
{
    _size = size;
}

QColor Mine::color() const
{
    return _color;
}

void Mine::setColor(QColor color)
{
    _color = color;
}

Qt::BrushStyle Mine::brushStyle() const
{
    return _brushStyle;
}

void Mine::setBrushStyle(const Qt::BrushStyle &brushStyle)
{
    _brushStyle = brushStyle;
}

QTime Mine::birthDate() const
{
    return _birthDate;
}

void Mine::setBirthDate(const QTime &birthDate)
{
    _birthDate = birthDate;
}

Mine::TypeMine Mine::type() const
{
    return _type;
}

void Mine::setType(const TypeMine &type)
{
    _type = type;
}


QPointF Mine::center() const
{
    qint32  x;
    qint32  y;

    x = ((*this)[0].x() + (*this)[1].x() + (*this)[2].x() + (*this)[3].x()) / 4;
    y = ((*this)[0].y() + (*this)[1].y() + (*this)[2].y() + (*this)[3].y()) / 4;
    return QPoint(x, y);
}

bool Mine::makeEntityMove()
{
    if (this->center().x() > SCREEN_SIZE
    ||  this->center().x() < 0)
    {
        this->angle(this->angle() - 180);
    }
    if (this->center().y() > SCREEN_SIZE
    ||  this->center().y() < 0)
    {
        this->angle(this->angle() - 180);
    }
    this->translate(_speed * cos(getRadian(_angle)), _speed * sin(getRadian(_angle)));
    return true;
}





