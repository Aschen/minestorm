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
