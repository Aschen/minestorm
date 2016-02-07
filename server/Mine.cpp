#include "Mine.hh"

Mine::Mine(qint32 id, TypeMine type, QPoint point, QTime birthDate) : Entity(id, Entity::MINE)
{
    this->setType(type);
    this->angle(rand() % 360);
    this->setBirthDate(birthDate);
    this->setBrushStyle(Qt::SolidPattern);

    this->_x = point.x();
    this->_y = point.y();
    this->_id = id;

    switch(type)
    {
        case Small:
            setSize(10);
            setColor(*new QColor(Qt::blue));
            break;
        case Medium:
            setSize(20);
            setColor(*new QColor(Qt::yellow));
            break;
        case Big:
            setSize(30);
            setColor(*new QColor(Qt::red));
    }
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

    x = _x;
    y = _y;
    return QPoint(x, y);
}







