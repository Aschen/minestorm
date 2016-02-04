#include "Element.hh"


Element::Element(qint32 id, const QPolygon &polygon)
    : _id(id),
      _polygon(polygon)
{
}

Element::Element()
{

}

Element::~Element()
{
}

qint32 Element::id() const
{
    return _id;
}

const QPolygon &Element::polygon() const
{
    return _polygon;
}
