#include "Element.hh"


Element::Element(qint32 imgId, const QPolygon &polygon)
    : _imgId(imgId),
      _polygon(polygon)
{
}

Element::Element()
{

}

Element::~Element()
{
}

qint32 Element::imgId() const
{
    return _imgId;
}

const QPolygon &Element::polygon() const
{
    return _polygon;
}
