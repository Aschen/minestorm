#include "Core.hh"

Core::Core(int cps) :
    QObject(),
    _isRunning(false),
    _cps(cps),
    _step(1)
{
    _timer.setSingleShot(false);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(step()));
}

void Core::step()
{
    DEBUG("Core::step() : " << _step, 1);
    ++_step;
}

void Core::start()
{
    if (_isRunning == false)
    {
        _timer.start(1000 / _cps); // Nombre de cycle de jeu par seconde
        _isRunning = true;
    }
    DEBUG("Core::start()", 1);
}

void Core::pause()
{
    if (_isRunning)
    {
        _timer.stop();
        _isRunning = false;
    }
    DEBUG("Core::pause()", 1);
}

void Core::reset()
{
    pause();
    DEBUG("Core::reset()", 1);
}

void Core::test()
{
    DEBUG("Core::test() : ", 1);
    Entity  ent("ent", Entity::SHIP);

    ent << QPoint(5 + _step, 5) << QPoint(5, 15) << QPoint(0, 15);
    _entities.push_back(std::shared_ptr<Entity>(new Entity(ent)));

    for (auto entity : _entities)
    {
        std::cout << entity->dump() << std::endl;
    }
}

void Core::mousePressed(int x, int y)
{
    DEBUG("Core::mousePressed : x = " << x << ", y = " << y, 1);

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

bool Core::addObject(const DrawableObject &object)
{
    if (_objects.find(object.name()) != _objects.end())
    {
        DEBUG("Core::addObject() : Object " << object.name() << " already exist", 1);
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
        DEBUG("Core::removeObject() : Object " << name << " doesn't exist", 1);
        return false;
    }

    _objects.erase(object_iterator);
    return true;
}

bool Core::removeObject(const DrawableObject &object)
{
    return removeObject(object.name());
}

