#include "DrawableObject.hh"

DrawableObject::DrawableObject(const std::string &name)
    : QPolygon(),
      _name(name)
{
}

DrawableObject::~DrawableObject()
{
}

const std::string &DrawableObject::name() const
{
    return _name;
}

