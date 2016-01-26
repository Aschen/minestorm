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
    DEBUG("Core::step() : " << _step, 0);
    QVector<QPolygon>   objects;

    // On créé un vecteur de QPolygon à partir de nos entitées
    for (auto entity : _entities)
    {
        objects.push_back(QPolygon(*entity));
    }

    // On envoi le vecteur de QPolygon à Display
    emit sendObjects(objects);
    ++_step;
}

void Core::start()
{
    DEBUG("Core::start()", 1);
    if (_isRunning == false)
    {
        _timer.start(1000 / _cps); // Nombre de cycle de jeu par seconde
        _isRunning = true;
    }
}

void Core::pause()
{
    DEBUG("Core::pause()", 1);
    if (_isRunning)
    {
        _timer.stop();
        _isRunning = false;
    }
}

void Core::reset()
{
    DEBUG("Core::reset()", 1);
    pause();
    _entities.clear();
    step();
    _step = 1;
}

void Core::test()
{
    DEBUG("Core::test() : ", 1);

    // Quand on reçoit un signal dans le slot test(),
    // On affiche la liste des entitées
    for (auto entity : _entities)
    {
        std::cout << entity->dump() << std::endl;
    }
}

void Core::mousePressed(int x, int y)
{
    DEBUG("Core::mousePressed : x = " << x << ", y = " << y, 1);

    // Quand on reçoit un signal dans le slot mousePressed(),
    // On créé un carre depuis les coordonnées x et y
    Carre   carre("carre", QPoint(x, y), _step);

    // On ajoute le triangle créé à la liste des entités
    _entities.push_back(std::shared_ptr<Entity>(new Carre(carre)));
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
