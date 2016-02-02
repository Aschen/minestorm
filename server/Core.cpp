#include "Core.hh"

Core::Core(qint32 cps)
    : QObject(),
      _isRunning(false),
      _cps(cps),
      _step(1),
      _server(4242)
{
    DEBUG("Core::Core() : cps " << cps, true);
    _timer.setSingleShot(false);
    connect(&_timer,    SIGNAL(timeout()),
            this,       SLOT(step()));

    // Connect communications functions
    connect(&_server,   SIGNAL(transfertMessage(qint32, const QString&)),
            this,       SLOT(messageDispatcher(qint32, const QString&)));

    _server.start();
    start();
}

Core::~Core()
{
    DEBUG("Core::~Core()", false);
}

void Core::step()
{
    DEBUG("Core::step() : " << _step, false);
    QVector<QPolygon>   objects;

    // On créé un vecteur de QPolygon à partir de nos entitées
    for (auto entity : _entities)
    {
        objects.push_back(QPolygon(*entity));
    }

    if (objects.size() && _server.clientCount())
    {
        DEBUG("Core::step() : Send " << objects.size() << " objects", false);
        MessageObjects      message(objects);

        _server.broadcast(message.messageString());
    }

    ++_step;
}

void Core::messageDispatcher(qint32 idClient, const QString &msg)
{
    DEBUG("Core::messageDispatcher() : client " << idClient << " : " << msg, false);
    qint32      type;
    MessageBase::Type   msgType;
    QTextStream stream(msg.toUtf8());

   stream >> type;
   msgType = (MessageBase::Type) type;

   if (msgType == MessageBase::MOUSE_PRESSED)
   {
       MessageMouse     message(msg);

       mousePressed(idClient, message.x(), message.y());
   }
   else
   {
       qDebug() << msg;
   }
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
}

void Core::mousePressed(qint32 idClient, qint32 x, qint32 y)
{
    qDebug() << "Core::mousePressed() : Client " << idClient << " x =" << x << ", y =" << y;

    // Quand on reçoit un signal dans le slot mousePressed(),
    // On créé un carre depuis les coordonnées x et y
    Carre   carre("carre", QPoint(x, y), 42);

    // On ajoute le carre créé à la liste des entités
    _entities.push_back(std::shared_ptr<Entity>(new Carre(carre)));
}

void Core::keyPressed(qint32 idClient, qint32 key)
{

}

void Core::keyReleased(qint32 idClient, qint32 key)
{

}
