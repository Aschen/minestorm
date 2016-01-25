#include "Mine.hh"

Mine::Mine(TypeMine type, QPoint point)
{
    _type = type;
    _point = point;
    _brushStyle = Qt::SolidPattern;
    switch(type)
    {
        case Small:
            _size = 10;
            _color = QColor(Qt::blue);
            break;
        case Medium:
            _size = 20;
            _color = QColor(Qt::yellow);
            break;
        case Big:
            _size = 30;
            _color = QColor(Qt::red);
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
QPoint Mine::point() const
{
    return _point;
}

void Mine::setPoint(const QPoint &point)
{
    _point = point;
}
Qt::BrushStyle Mine::brushStyle() const
{
    return _brushStyle;
}

void Mine::setBrushStyle(const Qt::BrushStyle &brushStyle)
{
    _brushStyle = brushStyle;
}








