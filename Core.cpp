#include "Core.hh"

Core::Core() :
    QObject()
{

}

bool Core::addObject(const DrawableObject &object)
{
    if (_objects.find(object.name()) != _objects.end())
    {
        DEBUG("Core::addObject() : Object " << object.name() << " already exist");
        return false;
    }

    _objects[object.name()] = std::shared_ptr<DrawableObject>(new DrawableObject(object));
    return true;
}

bool Core::removeObject(const std::string &name)
{
    auto object_iterator = _objects.find(name);
    if (object_iterator == _objects.end())
    {
        DEBUG("Core::removeObject() : Object " << name << " doesn't exist");
        return false;
    }

    _objects.erase(object_iterator);
    return true;
}

bool Core::removeObject(const DrawableObject &object)
{
    return removeObject(object.name());
}

void Core::mousePressed(int x, int y)
{
    DEBUG("Core::mousePressed : x = " << x << ", y = " << y);

    emit sendObjects(_objectsList);
}

void Core::mouseReleased(int x, int y)
{

}

void Core::mouseMoved(int x, int y)
{

}

void Core::keyPressed(int key)
{

}

void Core::keyReleased(int key)
{

}

