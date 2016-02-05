#include "Element.hh"


Element::Element(Type type, const QPolygon &polygon, qreal angle, const QPoint &center)
    : _type(type),
      _polygon(polygon),
      _angle(angle),
      _center(center)
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

const QPoint &Element::center() const
{
    return _center;
}

