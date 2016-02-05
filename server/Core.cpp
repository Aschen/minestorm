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

    Ship * nShip = new Ship(24);
    nShip->size(QSize(40,40));
    nShip->xy(QPoint(0,SCREEN_SIZE / 2));

    _entitiesMap[42] = QSharedPointer<Entity>(nShip);
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
    for (auto entity : _entitiesMap)
    {
        objects.push_back(QPolygon(*entity));
    }

    if (objects.size() && _server.clientCount())
    {
        DEBUG("Core::step() : Send " << objects.size() << " objects", false);
        MessageObjects      message(objects);

       // dynamic_cast<Ship*>(_entitiesMap[].data())-> moveShipForward();
        Collision c(_entitiesMap);
        for(QSharedPointer<Entity> &entity : _entitiesMap)
        {
            switch(entity->type())
            {
                case Entity::SHIP:
                {
                    Ship *ship = dynamic_cast<Ship*>(entity.data());
                    if(ship->speed() > 0)
                    {
                        ship->moveShipForward();
                        ship->speed(ship->speed() - 1);
                    }
                    break;
                }
                case Entity::MINE:
                {
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
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
    DEBUG("Core::NewPlayer() : " << idClient, true);
    Ship ship(idClient);
    ship.xy(QPoint(SCREEN_SIZE / 2, SCREEN_SIZE / 2));
    ship.size(QSize(42,42));
    ship.createShipPolygon();
    _entitiesMap[idClient] = QSharedPointer<Entity>(new Ship(ship));

    Ship ship1(22);
    ship1.xy(QPoint(0, 0));
    ship1.size(QSize(42,42));
    ship1.createShipPolygon();
    _entitiesMap[22] = QSharedPointer<Entity>(new Ship(ship1));

}

void Core::startGame()
{
    DEBUG("Core::startGame()", true);
    if (_isRunning == false)
    {
        _server.start();
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

    Ship ship(idClient);
    ship.xy(QPoint(SCREEN_SIZE / 2, SCREEN_SIZE /  2));
    ship.size(QSize(25,25));
    ship.createShipPolygon();

    _entitiesMap[idClient] = QSharedPointer<Entity>(new Ship(ship));
}


void Core::mousePressed(qint32 idClient, qint32 x, qint32 y)
{
    qDebug() << "Core::mousePressed() : Client " << idClient << " x =" << x << ", y =" << y;

    // Quand on reçoit un signal dans le slot mousePressed(),
    // On créé un carre depuis les coordonnées x et y
//    Carre   carre(_step, QPoint(x, y), 42);

//    // On ajoute le carre créé à la liste des entités
//    _entitiesMap[_step] = QSharedPointer<Entity>(new Carre(carre));

}

void Core::keyPressed(qint32 idClient, qint32 key)
{
    switch(key)
    {
    case Qt::Key_Right:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyRight", false);
        dynamic_cast<Ship*>(_entitiesMap[idClient].data())->rotateShipRight();

        break;

    case Qt::Key_Left:
        DEBUG("Core::keyPressed Client" << idClient << " KeyLeft", false);
        dynamic_cast<Ship*>(_entitiesMap[idClient].data())->rotateShipLeft();

        break;

    case Qt::Key_Up:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyUp", false);
        DEBUG("Ship::BMoved" <<  dynamic_cast<Ship*>(_entitiesMap[idClient].data())->xy().x(),false);
        dynamic_cast<Ship*>(_entitiesMap[idClient].data())->moveShipForward();


        DEBUG("Ship::AMoved" <<  dynamic_cast<Ship*>(_entitiesMap[idClient].data())->xy().x(),false);

        break;

    case Qt::Key_Down:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyDown", false);
        dynamic_cast<Ship*>(_entitiesMap[idClient].data())->slowDownShip();

        break;

    default:
        DEBUG("Core::keyPressed : Client" << idClient << " Unknown key:" << key, false);
        break;
    }
}

void Core::keyReleased(qint32 idClient, qint32 key)
{
    switch(key)
    {
    case Qt::Key_Right:
        DEBUG("Core::keyReleased : Client" << idClient << " KeyRight", false);
        break;

    case Qt::Key_Left:
        DEBUG("Core::keyReleased Client" << idClient << " KeyLeft", false);
        break;

    case Qt::Key_Up:
        DEBUG("Core::keyReleased : Client" << idClient << " KeyUp", false);
        break;

    case Qt::Key_Down:
        DEBUG("Core::keyReleased : Client" << idClient << " KeyDown", false);
        break;

    default:
        DEBUG("Core::keyReleased : Client" << idClient << " Unknown key:" << key, false);
        break;
    }

}
