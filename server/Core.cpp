#include "Core.hh"

Core::Core(qint32 cps)
    : QObject(),
      _isPlaying(false),
      _cps(cps),
      _step(1),
      _server(SERVER_PORT)
{
    DEBUG("Core::Core() : cps " << cps, false);

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
    DEBUG("Core::startGame()", false);
    _server.start();
    _timer.start(1000 / _cps); // Nombre de cycle de jeu par seconde
}

void Core::step()
{
    DEBUG("Core::step() : " << _step, false);

    if (_isPlaying)
    {
        bool    refreshPlayersInfo = false;

        Collision c(_entities);

        /* Repop mines toutes les 30 sec */
        if (_step % (CYCLE_PER_S * MINE_REPOP_DELAY) == 0)
        {
            initMines();
        }

        /* Move all ships */
        for (QSharedPointer<Entity> &entity : _entities[Entity::SHIP])
        {
            Ship    *ship = dynamic_cast<Ship*>(entity.data());

            /* Create shots */
            if (ship->isShooting(_step))
                addShot(QSharedPointer<Entity>(new Projectile(*ship)));

            /* Collide */
            c.detectShipCollision(entity);

            /* If live/scores changed, send infos to clients */
            if (ship->livesChanged() || ship->scoreChanged ())
                refreshPlayersInfo = true;

            /* Move */
            entity->makeEntityMove();

        }
        /* Move all mines */
        quint32     mineCount = 0;
        for (QSharedPointer<Entity> &entity : _entities[Entity::MINE])
        {
            c.detectMineCollision(entity);
            entity->makeEntityMove();
            mineCount++;
        }

        /* Move all shots */
        for (QSharedPointer<Entity> &entity : _entities[Entity::SHOT])
        {
            entity->makeEntityMove();
        }

        cleanEntities();

        /* Send score and lives to players */
        if (refreshPlayersInfo)
            sendPlayersInfos();

        /* Maintain fps rate */
        if (CYCLE_PER_S == 30)
        {
            if (_step % 4)
                sendObjects();
        }
        else
        {
            sendObjects();
        }

        /* respawn mines if none left */
        if (mineCount == 0)
        {
            initMines ();
        }
    }

    ++_step;
}

void Core::clientJoin(qint32 idClient)
{
    DEBUG("Core::clientJoint() : New client" << idClient, false);

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
        _spectators.push_back(idClient);
    }
}

void Core::clientLeft(qint32 idClient)
{
    /* If a player left */
    if (_players.contains(idClient))
    {
        DEBUG("Core::clientLeft() : Player left:" << idClient, true);
        _players.deletePlayer(idClient);

//        /* Make first spectator to play */
//        addShip (_players.newPlayer(_spectators.front()));
//        _spectators.pop_front();
    }
    else
    {
        DEBUG("Core::clientLeft() : Spectator left:" << idClient, true);
    }
}

void Core::initMines()
{
    qint32  x, y;

    //Small Mines
    for (quint32 i = 0; i < 3; ++i)
    {
        x = rand() % (SCREEN_WIDTH - 20) + 10;
        y = rand() % (SCREEN_HEIGHT - 20) + 10;
        DEBUG("Core::initMines() Mine(" << x << "," << y << ")", false);

        addMine(Mine::TypeMine::Small, x, y);
    }

    for (quint32 i = 0; i < 3; ++i)
    {
        x = rand() % SCREEN_WIDTH - 10;
        y = rand() % SCREEN_HEIGHT - 10;
        DEBUG("Core::initMines() Mine(" << x << "," << y << ")", false);

        addMine(Mine::TypeMine::Medium, x, y);
    }

    for (quint32 i = 0; i < 3; ++i)
    {
        x = rand() % SCREEN_WIDTH - 10;
        y = rand() % SCREEN_HEIGHT - 10;
        DEBUG("Core::initMines() Mine(" << x << "," << y << ")", false);

        addMine(Mine::TypeMine::Big, x, y);
    }
}

void Core::addMine(Mine::TypeMine type, quint32 x, quint32 y)
{
    _entities[Entity::MINE].push_back(QSharedPointer<Entity>(new Mine(type, QPointF(x, y))));
}

void Core::addShip(QSharedPointer<Entity> &ship)
{
    _entities[Entity::SHIP].push_back(ship);
}

void Core::addShot(QSharedPointer<Entity> shot)
{
    _entities[Entity::SHOT].push_back(shot);
}

void Core::cleanEntities()
{
    EntityList  &shots = _entities[Entity::SHOT];
    EntityList  &ships = _entities[Entity::SHIP];
    EntityList  &mines = _entities[Entity::MINE];

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

void Core::sendPlayersInfos()
{
    MessagePlayersInfos     msg(_players);

    _server.broadcast(msg.messageString ());
}

void Core::sendObjects()
{
    /* Merge the lists */
    EntityList          entitiesList;

    for (const EntityList &list : _entities)
        entitiesList += list;

    /* Send entities list to clients */
    MessageObjects      message(entitiesList);
    _server.broadcast(message.messageString());
}

/**********\
|* EVENTS *|
\**********/

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
            DEBUG("Core::messageDispatcher() : KeyPRESSED" << msg, false);
            MessageKey          message(msg);
            keyPressed(idClient, message.keyCode());
            break;
        }
        case MessageBase::KEY_RELEASE:
        {
            DEBUG("Core::messageDispatcher() : KeyRelease" << msg, false);
            MessageKey          message(msg);
            keyReleased(idClient, message.keyCode());
            break;
        }
        case MessageBase::PSEUDO:
        {
            MessagePseudo       message(msg);
            _players.playerPseudo(idClient, message.pseudo());
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
        _players.keyPressRight(idClient);
        break;

    case Qt::Key_Left:
        DEBUG("Core::keyPressed Client" << idClient << " KeyLeft", false);
        _players.keyPressLeft(idClient);
        break;

    case Qt::Key_Up:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyUp", false);
        _players.keyPressUp(idClient);
        break;

    case Qt::Key_Down:
        DEBUG("Core::keyPressed : Client" << idClient << " KeyDown", false);
        _players.keyPressDown(idClient);
        break;

    case Qt::Key_Space:
    {
        DEBUG("Core::keyPressed : Client " << idClient << " KeySpace", false);
        if (_players.findPlayer(idClient)->lives())
            addShot(_players.keyPressSpace(idClient));
        break;
    }
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
            DEBUG("Core::keyRealeased : Client" << idClient << " KeyRight", false);
            _players.keyReleaseRight(idClient);
            break;

        case Qt::Key_Left:
            DEBUG("Core::keyRealeased Client" << idClient << " KeyLeft", false);
            _players.keyReleaseLeft(idClient);
            break;

        case Qt::Key_Up:
            DEBUG("Core::keyRealeased Client" << idClient << " KeyUp", false);
            _players.keyReleaseUp(idClient);
            break;

        case Qt::Key_Space:
            DEBUG("Core::keyRealeased Client" << idClient << " KeySpace", false);
            _players.keyReleaseSpace(idClient);
            break;

        default:
            DEBUG("Core::keyReleased : Client" << idClient << " Unknown key:" << key, false);
            break;
    }
}
