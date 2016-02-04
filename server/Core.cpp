#include "Core.hh"

Core::Core(qint32 cps)
    : QObject(),
      _isRunning(false),
      _cps(cps),
      _step(1),
      _server(SERVER_PORT),
      _playersCount(1)
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
    connect(&_server,   SIGNAL(sigClientDisconnected(qint32)),
            this,       SLOT(playerLeft(qint32)));
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

       // dynamic_cast<Ship*>(_entitiesMap[].data())-> moveShipForward();

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
    if (_playersCount <= MAX_PLAYERS)
    {
        DEBUG("Core::NewPlayer() : " << idClient, true);
        Ship ship(idClient);
        ship.xy(QPoint(SCREEN_SIZE / 2, SCREEN_SIZE / 2));
        ship.size(QSize(42,42));
        ship.createShipPolygon();
        ship.shipNumber (_playersCount);

        _entitiesMap[idClient] = QSharedPointer<Entity>(new Ship(ship));
        _playersCount++;
    }
    else
    {
        DEBUG("Display::initialize() : New spectator" << idClient, 0);
    }
}

void Core::playerLeft(qint32 idClient)
{
    DEBUG("Core::playerLeft() : " << idClient, true);

    _entitiesMap.erase(_entitiesMap.find(idClient));
    _playersCount--;
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

void Core::initialize(qint32 idClient)
{
}


void Core::mousePressed(qint32 idClient, qint32 x, qint32 y)
{
    qDebug() << "Core::mousePressed() : Client " << idClient << " x =" << x << ", y =" << y;
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
    (void) idClient;
    (void) key;
}
