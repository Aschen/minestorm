#include "Element.hh"


Element::Element(Type type, const QPolygon &polygon, qreal angle, const QPoint &center)
    : _type(type),
      _polygon(polygon),
      _angle(angle),
      _center(center),
      _imageCenter(_center.x() - 16, _center.y() - 16)
{
}
Element::Element(Type type, const QPolygon &polygon)
    : _type(type),
      _polygon(polygon),
      _angle(0.0)
{
}

Element::Element(Element::Type type, const QPolygon &polygon, quint32 armed, const QPoint &center)
    : _type(type),
      _polygon(polygon),
      _armed(armed),
      _center(center)
{
}

Element::Element()
{
}

Element::~Element()
{
}

void Element::draw(QPainter &painter)
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

quint32 Element::armed() const
{
    return _armed;
}

const QPoint &Element::center() const
{
    return _center;
}

const QPoint &Element::imageCenter() const
{
    return _imageCenter;
}

