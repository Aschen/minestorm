#include "Element.hh"


Element::Element(Type type, const QPolygon &polygon)
    : _type(type),
      _polygon(polygon)
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

QPoint Element::center() const
{
    qint32      x;
    qint32      y;

    if (_polygon.size() == 3)
    {
        DEBUG("Element::center() : 3 points", true);
        x = (_polygon[0].x() + _polygon[1].x() + _polygon[2].x()) / 3;
        y = (_polygon[0].y() + _polygon[1].y() + _polygon[2].y()) / 3;
        return QPoint(x, y);
    }

    return QPoint(200, 200);
}


