#include "Core.hh"

Core::Core(qint32 cps)
    : QObject(),
      _isRunning(false),
      _cps(cps),
      _step(1),
      _server(SERVER_PORT),
      _playersCount(0),
      _playerSpawn(MAX_PLAYERS + 1)
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

    // Initialize players spawn
    qint32      screenPart = SCREEN_SIZE / 4;

    _playerSpawn[1] = QPoint(1 * screenPart, 1 * screenPart);
    _playerSpawn[2] = QPoint(3 * screenPart, 1 * screenPart);
    _playerSpawn[3] = QPoint(3 * screenPart, 3 * screenPart);
    _playerSpawn[4] = QPoint(1 * screenPart, 3 * screenPart);
}

Core::~Core()
{
    DEBUG("Core::~Core()", false);
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

void Core::step()
{
    DEBUG("Core::step() : " << _step, false);

    if (!_entitiesMap.empty() && _server.clientCount())
    {
       DEBUG("Core::step() : Send " << _entitiesMap.size() << " objects", false);

       for(QSharedPointer<Entity> &entity : _entitiesMap)
       {
           entity->makeEntityMove();

           //En cours : a ne faire que pour les tirs (et les mines ?)
           if(entity->isDead())
               _entitiesToDelete.push_back(entity);
       }
       removeEntitiesToDelete();

       Collision            c(_entitiesMap, _entitiesToDelete);
       removeEntitiesToDelete();

       MessageObjects      message(_entitiesMap);

        _server.broadcast(message.messageString());
    }

    ++_step;
}

void Core::removeEntitiesToDelete()
{
    for (QSharedPointer<Entity> &entity : _entitiesToDelete)
    {
        // Move player to spectator if ship is dead
        if (entity->type() == Entity::SHIP)
        {
            _playersInGame.removeOne(entity->id());
        }
        _entitiesMap.remove(entity->id());
    }
}


/**
 * @brief Core::newPlayer : Instancie un nouveau vaisseau lors de la connexion d'un client
 *                          Appelé par le signal clientConnected.
 * @param idClient        : id de la socket client
 */
void Core::newPlayer(qint32 idClient)
{
    if (_server.clientCount() <= MAX_PLAYERS)
    {
        DEBUG("Core::NewPlayer() : " << idClient, true);
        if(_playersCount == 0)
            entitiesInitialization();

        _playersCount++;

        _entitiesMap[idClient] = QSharedPointer<Entity>(
                    new Ship(idClient, _playerSpawn[_playersCount], _playersCount)
                    );

        // Add player to active players list
        _playersInGame.push_back(idClient);
    }
    else
    {
        DEBUG("Core::initialize() : New spectator" << idClient, true);
    }
}

void Core::playerLeft(qint32 idClient)
{
    DEBUG("Core::playerLeft() : " << idClient, true);

    auto it = _entitiesMap.find(idClient);

    if (it != _entitiesMap.end())
    {
        _playersCount--;
        _entitiesMap.remove(idClient);

        // Delete player from active players list
        _playersInGame.removeOne(idClient);
    }
}

void Core::entitiesInitialization()
{
    DEBUG("Core::entitiesInit() - entitiesMaps.size() = " << _entitiesMap.size(), true);
    int i, x, y;

    i = 0;
    //Small Mines
    while (i < 5)
    {
        x = rand() % (SCREEN_SIZE - 20) + 10;
        y = rand() % (SCREEN_SIZE - 20) + 10;
        QTime time = QTime::currentTime();
        time = time.addSecs(rand() % 15 + 1);
        DEBUG("Mine(" << x << "," << y << ")", false);

        this->_entitiesMap[MAX_CLIENTS + i] = QSharedPointer<Entity>(new Mine(MAX_CLIENTS + i, Mine::TypeMine::Small, *new QPointF(x, y), time));
        i++;
    }

    while (i < 5)
    {
        x = rand() % SCREEN_SIZE - 10;
        y = rand() % SCREEN_SIZE - 10;
        QTime time = QTime::currentTime();
        time = time.addSecs(rand() % 15 + 1);
        DEBUG("Mine(" << x << "," << y << ")", false);
        this->_entitiesMap[MAX_CLIENTS + i] = QSharedPointer<Entity>(new Mine(MAX_CLIENTS + i, Mine::TypeMine::Big, *new QPoint(x, y), time));
        i++;
    }

    while (i < 10)
    {
        x = rand() % SCREEN_SIZE - 10;
        y = rand() % SCREEN_SIZE - 10;
        QTime time = QTime::currentTime();
        time = time.addSecs(rand() % 15 + 1);
        DEBUG("Mine(" << x << "," << y << ")", false);
        this->_entitiesMap[MAX_CLIENTS + i] = QSharedPointer<Entity>(new Mine(MAX_CLIENTS + i, Mine::TypeMine::Medium, *new QPoint(x, y), time));
        i++;
    }

    DEBUG("entitiesMaps.size() = " << _entitiesMap.size(), true);
}

/**********\
|* EVENTS *|
\**********/

void Core::messageDispatcher(qint32 idClient, const QString &msg)
{
    DEBUG("Core::messageDispatcher() : client " << idClient << " : " << msg, false);

    if (_playersInGame.contains(idClient))
    {
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
        default:
        {
            DEBUG("Core::messageDispatcher() : Unknown message" << msg, true);
            break;
        }
        }
    }
    else
    {
        DEBUG("Core::messageDispatcher() : client " << idClient << " is a spectator", true);
    }
}

void Core::mousePressed(qint32 idClient, qint32 x, qint32 y)
{
    DEBUG("Core::mousePressed() : Client " << idClient << " x =" << x << ", y =" << y, false);
}

void Core::keyPressed(qint32 idClient, qint32 key)
{
    switch(key)
    {
    case Qt::Key_Right:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyRight", false);
        dynamic_cast<Ship*>(_entitiesMap[idClient].data())->rotate(15);

        break;

    case Qt::Key_Left:
        DEBUG("Core::keyPressed Client" << idClient << " KeyLeft", false);
        dynamic_cast<Ship*>(_entitiesMap[idClient].data())->rotate(-15);

        break;

    case Qt::Key_Up:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyUp", false);

        dynamic_cast<Ship*>(_entitiesMap[idClient].data())->incrementSpeed();
        break;

    case Qt::Key_Down:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyDown", false);
        dynamic_cast<Ship*>(_entitiesMap[idClient].data())->decrementSpeed();

        break;

    case Qt::Key_Space:
    {
        DEBUG("Core::keyPressed : Client " << idClient << " KeySpace", true);
        int id = rand();
        _entitiesMap[id] = QSharedPointer<Entity>(new Projectile(id, *dynamic_cast<Ship*>(_entitiesMap[idClient].data())));
        break;
    }

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
