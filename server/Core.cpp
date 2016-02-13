#include "Core.hh"

Core::Core(qint32 cps)
    : QObject(),
      _isRunning(false),
      _cps(cps),
      _step(1),
      _server(SERVER_PORT),
      _playersCount(0),
      _playerSpawn(MAX_PLAYERS + 1),
      _uniqId(100),
      _players(0)
{
    DEBUG("Core::Core() : cps " << cps, true);

    /* Start Core timer */
    _timer.setSingleShot(false);
    connect(&_timer,    SIGNAL(timeout()),
            this,       SLOT(step()));

    /* Connect communications functions */
    connect(&_server,   SIGNAL(transfertMessage(qint32, const QString&)),
            this,       SLOT(messageDispatcher(qint32, const QString&)));
    connect(&_server,   SIGNAL(clientConnected(qint32)),
            this,       SLOT(newPlayer(qint32)));
    connect(&_server,   SIGNAL(sigClientDisconnected(qint32)),
            this,       SLOT(playerLeft(qint32)));


    /* Initialize 4 players */
    initPlayers();
}

void Core::initPlayers()
{
    qint32      screenPart = SCREEN_SIZE / 4;

    _players.push_back(QSharedPointer<Player>(new Player(1, QPoint(1 * screenPart, 1 * screenPart))));
    _players.push_back(QSharedPointer<Player>(new Player(2, QPoint(3 * screenPart, 1 * screenPart))));
    _players.push_back(QSharedPointer<Player>(new Player(3, QPoint(3 * screenPart, 3 * screenPart))));
    _players.push_back(QSharedPointer<Player>(new Player(4, QPoint(1 * screenPart, 3 * screenPart))));
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
        DEBUG("Core::step() : " << _entitiesMap.size() << " entities", false);

        /* Movements */
        for(QSharedPointer<Entity> &entity : _entitiesMap)
        {
            entity->makeEntityMove();

            //En cours : a ne faire que pour les tirs (et les mines ?)
            if(entity->isDead())
                _entitiesToDelete.push_back(entity);
        }
        removeEntitiesToDelete();

        /* Collision */
        Collision            c(_entitiesMap, _entitiesToDelete);

        /* Send score and lives to clients */
        for (qint32 idClient : _playersInGame)
        {
            Ship    *ship = dynamic_cast<Ship*>(_entitiesMap[idClient].data());

            if (ship->scoreChanged())
            {
                MessageScore    msg(ship->score());
                _server.unicast(idClient, msg.messageString ());
            }
            if (ship->livesChanged())
            {
                MessageLives    msg(ship->vie());
                _server.unicast(idClient, msg.messageString());
            }
        }
        removeEntitiesToDelete();

        /* Send objects list to clients */
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
    qint32      i;

    /* If there is a room for new player */
    if ((i = playerAvailable()) != -1)
    {
        DEBUG("Core::NewPlayer() : " << idClient, true);

        /* Init mines if first player */
        if (playersCount() == 0)
            initMine();

        _entitiesMap[idClient] = _players[i]->newPlayer(idClient);

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
    auto it = std::find_if(_players.first(),
                           _players.end(),
                           [idClient](const QSharedPointer<Player> &player) { return player->idClient() == idClient; });

    /* If client is in players */
    if (it != _players.end())
    {
        QSharedPointer<Player> &player = *it;

        player->playerLeft();
    }


//    auto it = _entitiesMap.find(idClient);

//    if (it != _entitiesMap.end())
//    {
//        _playersCount--;
//        _entitiesMap.remove(idClient);

//        // Delete player from active players list
//        _playersInGame.removeOne(idClient);
//    }
}

void Core::initMines()
{
    DEBUG("Core::initMines() - entitiesMaps.size() = " << _entitiesMap.size(), true);
    qint32  x, y, id;

    //Small Mines
    for (quint32 i = 0; i < 2; ++i)
    {
        x = rand() % (SCREEN_SIZE - 20) + 10;
        y = rand() % (SCREEN_SIZE - 20) + 10;
        DEBUG("Core::initMines() Mine(" << x << "," << y << ")", false);

        id = getID();
        this->_entitiesMap[id] = QSharedPointer<Entity>(new Mine(id,
                                                                 Mine::TypeMine::Small,
                                                                 QPointF(x, y)));
    }

    for (quint32 i = 0; i < 2; ++i)
    {
        x = rand() % SCREEN_SIZE - 10;
        y = rand() % SCREEN_SIZE - 10;
        DEBUG("Core::initMines() Mine(" << x << "," << y << ")", false);

        id = getID();
        this->_entitiesMap[id] = QSharedPointer<Entity>(new Mine(id,
                                                                 Mine::TypeMine::Big,
                                                                 QPoint(x, y)));
    }

    for (quint32 i = 0; i < 2; ++i)
    {
        x = rand() % SCREEN_SIZE - 10;
        y = rand() % SCREEN_SIZE - 10;
        DEBUG("Core::initMines() Mine(" << x << "," << y << ")", false);

        id = getID();
        this->_entitiesMap[id] = QSharedPointer<Entity>(new Mine(id,
                                                                 Mine::TypeMine::Medium,
                                                                 QPoint(x, y)));
    }

    DEBUG("Core::initMines()entitiesMaps.size() = " << _entitiesMap.size(), true);
}

quint32 Core::getID()
{
    return ++_uniqId;
}

quint32 Core::playersCount() const
{
    quint32     i = 0;

    for (QSharedPointer<Player> &player : _players)
    {
        i += player->available() ? 1 : 0;
    }

    return i;
}

qint32 Core::playerAvailable() const
{
    for (quint32 i = 0; i < _players.size (); ++i)
    {
        if (_players[i]->available())
        {
            return i;
        }
    }

    return -1;
}

/**********\
|* EVENTS *|
\**********/

void Core::scoreChanged(qint32 idClient, quint32 score)
{
    DEBUG("Core::newScore() : client:" << idClient << " score:" << score, true);
    MessageScore        msg(score);

    _server.unicast(idClient, msg.messageString());
}

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
        dynamic_cast<Ship*>(_entitiesMap[idClient].data())->decrementSpeed(5);

        break;

    case Qt::Key_Space:
    {
        DEBUG("Core::keyPressed : Client " << idClient << " KeySpace", false);
        quint32     id = getID();
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
