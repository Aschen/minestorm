#include "Core.hh"

Core::Core(qint32 cps)
    : QObject(),
      _isPlaying(false),
      _cps(cps),
      _step(1),
      _server(SERVER_PORT),
      _uniqId(100)
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
            this,       SLOT(clientJoin(qint32)));
    connect(&_server,   SIGNAL(sigClientDisconnected(qint32)),
            this,       SLOT(clientLeft(qint32)));

    _entities[Entity::SHIP] = EntityList();
    _entities[Entity::MINE] = EntityList();
    _entities[Entity::SHOT] = EntityList();

}

void Core::startGame()
{
    DEBUG("Core::startGame()", true);
    _server.start();
    _timer.start(1000 / _cps); // Nombre de cycle de jeu par seconde
}

void Core::step()
{
    DEBUG("Core::step() : " << _step, false);

    if (_isPlaying)
    {
        /* Move all ships */
        for (QSharedPointer<Entity> &entity : _entities[Entity::SHIP])
        {
            entity->makeEntityMove();
        }
        /* Move all mines */
        for (QSharedPointer<Entity> &entity : _entities[Entity::MINE])
        {
            entity->makeEntityMove();
        }
        /* Move all shots */
        for (QSharedPointer<Entity> &entity : _entities[Entity::SHOT])
        {
            entity->makeEntityMove();
        }

        cleanEntities();

        /* Collision */
//        Collision            c(_entitiesMap, _entitiesToDelete);

        /* Send score and lives to players */
        for (const QSharedPointer<Player> &player : _players)
        {
            if (player->ship().scoreChanged())
            {
                MessageScore    msg(player->ship().score());
                _server.unicast(player->idClient(), msg.messageString());
            }
            if (player->ship().livesChanged())
            {
                MessageLives    msg(player->ship().vie());
                _server.unicast(player->idClient(), msg.messageString());
            }
        }

        /* Merge the lists */
        EntityList          entitiesList;
        for (const EntityList &list : _entities)
            entitiesList += list;

        /* Send entities list to clients */
        MessageObjects      message(entitiesList);
        _server.broadcast(message.messageString());
    }

//    if (!_entitiesMap.empty() && _server.clientCount())
//    {
//        DEBUG("Core::step() : Send " << _entitiesMap.size() << " objects", false);
//        DEBUG("Core::step() : " << _entitiesMap.size() << " entities", false);

//        /* Movements */
//        for(QSharedPointer<Entity> &entity : _entitiesMap)
//        {
//            entity->makeEntityMove();

//            //En cours : a ne faire que pour les tirs (et les mines ?)
//            if(entity->isDead())
//                _entitiesToDelete.push_back(entity);
//        }
//        removeEntitiesToDelete();

//        /* Collision */
//        Collision            c(_entitiesMap, _entitiesToDelete);

//        /* Send score and lives to players */
//        for (const QSharedPointer<Player> &player : _players)
//        {
//            if (player->ship().scoreChanged())
//            {
//                MessageScore    msg(player->ship().score());
//                _server.unicast(player->idClient(), msg.messageString());
//            }
//            if (player->ship().livesChanged())
//            {
//                MessageLives    msg(player->ship().vie());
//                _server.unicast(player->idClient(), msg.messageString());
//            }
//        }
//        removeEntitiesToDelete();

//        /* Send objects list to clients */
//        MessageObjects      message(_entitiesMap);
//        _server.broadcast(message.messageString());

//    }

    ++_step;
}

void Core::removeEntitiesToDelete()
{
    for (QSharedPointer<Entity> &entity : _entitiesToDelete)
    {
        // Move player to spectator if ship is dead
        if (entity->type() == Entity::SHIP)
        {
            _players.deletePlayer(entity->id());
        }
        _entitiesMap.remove(entity->id());
    }
}

void Core::clientJoin(qint32 idClient)
{
    DEBUG("Core::clientJoint() : New client" << idClient, true);

    if (_players.playerAvailable() && !_players.contains(idClient))
    {
        DEBUG("Core::clientJoint() : New player" << idClient, true);

        /* Init mines if first player */
        if (_players.count() == 0)
        {
            _isPlaying = true;
            initMines();
        }

        /* Create new player and add ship to entities */
        addShip(_players.newPlayer(idClient));
    }
    else
    {
        DEBUG("Core::clientJoint() : New spectator" << idClient, true);
    }
}

void Core::clientLeft(qint32 idClient)
{
    /* If a player left */
    if (_players.contains(idClient))
    {
        DEBUG("Core::clientLeft() : Player left:" << idClient, true);

        _players.deletePlayer(idClient);
//        _entitiesMap.remove(idClient); // Handle this in cleanEntities
    }
    else
    {
        DEBUG("Core::clientLeft() : Spectator left:" << idClient, true);
    }
}

void Core::initMines()
{
    DEBUG("Core::initMines() - entitiesMaps.size() = " << _entitiesMap.size(), true);
    qint32  x, y;

    //Small Mines
    for (quint32 i = 0; i < 2; ++i)
    {
        x = rand() % (SCREEN_SIZE - 20) + 10;
        y = rand() % (SCREEN_SIZE - 20) + 10;
        DEBUG("Core::initMines() Mine(" << x << "," << y << ")", false);

        quint32 obsolete = 42;
        addMine(obsolete, Mine::TypeMine::Small, x, y);
    }

    for (quint32 i = 0; i < 2; ++i)
    {
        x = rand() % SCREEN_SIZE - 10;
        y = rand() % SCREEN_SIZE - 10;
        DEBUG("Core::initMines() Mine(" << x << "," << y << ")", false);

        quint32 obsolete = 42;
        addMine(obsolete, Mine::TypeMine::Medium, x, y);
    }

    for (quint32 i = 0; i < 2; ++i)
    {
        x = rand() % SCREEN_SIZE - 10;
        y = rand() % SCREEN_SIZE - 10;
        DEBUG("Core::initMines() Mine(" << x << "," << y << ")", false);

        quint32 obsolete = 42;
        addMine(obsolete, Mine::TypeMine::Big, x, y);
    }

    DEBUG("Core::initMines() entitiesMaps.size() = " << _entitiesMap.size(), true);
}

void Core::addMine(quint32 id, Mine::TypeMine type, quint32 x, quint32 y)
{
    _entities[Entity::MINE].push_back(QSharedPointer<Entity>(new Mine(id, type, QPointF(x, y))));
}

void Core::addShip(QSharedPointer<Entity> &ship)
{
    _entities[Entity::SHIP].push_back(ship);
}

void Core::addShot(QSharedPointer<Entity> &shot)
{
    _entities[Entity::SHOT].push_back(shot);
}

void Core::cleanEntities()
{
    EntityList  &ships = _entities[Entity::SHIP];
    EntityList  &mines = _entities[Entity::MINE];
    EntityList  &shots = _entities[Entity::SHOT];

    /* Erase dead ships */
    for (EntityList::iterator it = ships.begin(); it != ships.end();)
    {
        if ((*it)->isDead())
        {
            it = ships.erase(it);
        }
        else
        {
            ++it;
        }
    }

    /* Erase dead mines */
    for (EntityList::iterator it = mines.begin(); it != mines.end();)
    {
        if ((*it)->isDead())
        {
            it = mines.erase(it);
        }
        else
        {
            ++it;
        }
    }

    /* Erase dead shots */
    for (EntityList::iterator it = shots.begin(); it != shots.end();)
    {
        if ((*it)->isDead())
        {
            it = shots.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

quint32 Core::getID()
{
    return ++_uniqId;
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

    if (_players.contains(idClient))
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
