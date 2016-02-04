#include "Element.hh"


Element::Element(Type type, const QPolygon &polygon, qreal angle)
    : _type(type),
      _polygon(polygon),
      _angle(angle)
{
}

Element::Element()
{
}

Element::~Element()
{
}

Element::Type Element::type() const
{
    return _type;
}

const QPolygon &Element::polygon() const
{
    return _polygon;
}

qreal Element::angle() const
{
    return _angle;
}

QPoint Element::center() const
{
    switch (_type)
    {
    case SHIP_1:
    case SHIP_2:
    case SHIP_3:
    case SHIP_4:
        return QPoint(_polygon[0].x(), _polygon[0].y());
        break;
    case MINE:
        break;
    }
}

