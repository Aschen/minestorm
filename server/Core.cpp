#include "Core.hh"
#include "Ship.hh"

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

    MessageBase::Type       msgType = MessageBase::getMessageType(msg);

    switch (msgType)
    {
    case MessageBase::MOUSE_PRESSED:
    case MessageBase::MOUSE_RELEASED:
    {
        MessageMouse        message(msg);

        mousePressed(idClient, message.x(), message.y());
        break;
    }
    default:
    {
        DEBUG("Core::messageDispatcher() : Unknown message" << msg, true);
        break;
    }
    }
}

void Core::start()
{
    DEBUG("Core::start()", 1);
    if (_isRunning == false)
    {
        _timer.start(1000 / _cps); // Nombre de cycle de jeu par seconde
        _isRunning = true;
        //initialize(12,1);
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

void Core::initialize(qint32 idClient, QSize size)
{
    DEBUG("Display::initialize()", 0);

    Ship ship(idClient,QRect(size.width()/2-40/2,size.height()/2-40/2,40,40), 3);
    QPolygon polygon = QPolygon(ship.rect(), true);

    _entities.push_back(std::shared_ptr<Entity>(new Ship(ship)));
    _entitiesMap[idClient] = _entities.last();
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
    switch(key)
    {
    case Qt::Key_Right:
        DEBUG("Display::KeyRight"<<idClient, true);

    break;
    case Qt::Key_Left:
        DEBUG("Display::KeyLeft"<<idClient, true);

    break;
    case Qt::Key_Up:
        DEBUG("Display::KeyUp"<<idClient, true);

    break;
    case Qt::Key_Down:
        DEBUG("Display::KeyDown"<<idClient, true);

    break;
    default:

    break;
    }
}

void Core::keyReleased(qint32 idClient, qint32 key)
{

}
