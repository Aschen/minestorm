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

    connect(&_server,   SIGNAL(clientConnected(qint32)),
            this,       SLOT(newPlayer(qint32)));

}

Core::~Core()
{
    DEBUG("Core::~Core()", false);
}

void Core::step()
{
    DEBUG("Core::step() : " << _step, false);

    if (!_entitiesMap.empty() && _server.clientCount())
    {
        DEBUG("Core::step() : Send " << _entitiesMap.size() << " objects", false);
        MessageObjects      message(_entitiesMap);

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
    {
        MessageMouse        message(msg);

        mousePressed(idClient, message.x(), message.y());
        break;
    }
    case MessageBase::KEY_PRESSED:
    {
        MessageKey          message(msg);

        keyPressed(idClient, message.keyCode());
        break;
    }
    case MessageBase::KEY_RELEASED:
    {
        MessageKey          message(msg);

        keyReleased(idClient, message.keyCode());
        break;
    }
    default:
    {
        DEBUG("Core::messageDispatcher() : Unknown message" << msg, true);
        break;
    }
    }
}

void Core::newPlayer(qint32 idClient)
{

}

void Core::startGame()
{
    DEBUG("Core::startGame()", true);
    if (_isRunning == false)
    {
        _server.start();
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
    _entitiesMap.clear();
    step();
    _step = 1;
}

void Core::test()
{
    DEBUG("Core::test() : ", 1);
}

void Core::initialize(qint32 idClient)
{
    DEBUG("Display::initialize()", 0);

////<<<<<<< HEAD
//    Ship ship(idClient,QRect(size.width()/2-40/2,size.height()/2-40/2,40,40), 3, 0);
//    QPolygon polygon = QPolygon(ship.rect(), true);
////=======
    Ship ship(idClient);
    ship.xy(QPoint(SCREEN_SIZE / 2, SCREEN_SIZE /  2));
    ship.size(QSize(25,25));
    ship.createShipPolygon();

//>>>>>>> da38e671911a97810df6a31e728546ee32c4d6e7

    _entitiesMap[idClient] = QSharedPointer<Entity>(new Ship(ship));
}


void Core::mousePressed(qint32 idClient, qint32 x, qint32 y)
{
    qDebug() << "Core::mousePressed() : Client " << idClient << " x =" << x << ", y =" << y;

    // Quand on reçoit un signal dans le slot mousePressed(),
    // On créé un carre depuis les coordonnées x et y
    Carre   carre(_step, QPoint(x, y), 42, idClient * idClient * idClient % 255);

    // On ajoute le carre créé à la liste des entités
    _entitiesMap[_step] = QSharedPointer<Entity>(new Carre(carre));
}

void Core::keyPressed(qint32 idClient, qint32 key)
{
    switch(key)
    {
    case Qt::Key_Right:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyRight", true);
        break;

    case Qt::Key_Left:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyLeft", true);
        break;

    case Qt::Key_Up:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyUp", true);
        break;

    case Qt::Key_Down:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyDown", true);
        break;

    default:
        DEBUG("Core::keyPressed : Client" << idClient << " Unknown key:" << key, true);
        break;
    }
}

void Core::keyReleased(qint32 idClient, qint32 key)
{
    switch(key)
    {
    case Qt::Key_Right:
        DEBUG("Core::keyReleased : Client" << idClient << " KeyRight", true);
        break;

    case Qt::Key_Left:
        DEBUG("Core::keyReleased Client" << idClient << " KeyLeft", true);
        break;

    case Qt::Key_Up:
        DEBUG("Core::keyReleased : Client" << idClient << " KeyUp", true);
        break;

    case Qt::Key_Down:
        DEBUG("Core::keyReleased : Client" << idClient << " KeyDown", true);
        break;

    default:
        DEBUG("Core::keyReleased : Client" << idClient << " Unknown key:" << key, true);
        break;
    }

}
