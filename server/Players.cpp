#include "Players.hh"

Players::Players(qint32 maxPlayers)
    : _maxPlayers(maxPlayers),
      _spawns(maxPlayers)
{
    _spawns[0] = QPoint(1 * SCREEN_SIZE / 4, 1 * SCREEN_SIZE / 4);
    _spawns[1] = QPoint(1 * SCREEN_SIZE / 4, 3 * SCREEN_SIZE / 4);
    _spawns[2] = QPoint(3 * SCREEN_SIZE / 4, 3 * SCREEN_SIZE / 4);
    _spawns[3] = QPoint(3 * SCREEN_SIZE / 4, 1 * SCREEN_SIZE / 4);
}

QSharedPointer<Player> &Players::findPlayer(qint32 idClient)
{
    for (QSharedPointer<Player> &player : *this)
    {
        if (player->idClient() == idClient)
            return player;
    }
    assert(false);
}

QSharedPointer<Entity> &Players::newPlayer(qint32 idClient)
{
    assert(this->playerAvailable());
    DEBUG("Players::newPlayer() idClient:" << idClient , false);


    /* Create new player */
    this->push_back(QSharedPointer<Player>(new Player(idClient,
                                                      this->size() + 1,
                                                      _spawns[this->size()])));

    /* Return QSharedPointer<Entity> to add in Core::_entitiesMap */
    return this->last()->entity();
}

void Players::deletePlayer(qint32 idClient)
{
    for (auto it = this->begin(); it != this->end(); ++it)
    {
        if ((*it)->idClient() == idClient)
        {
            this->erase(it);
            break;
        }
    }
}

/* EVENTS */
void Players::keyRight(qint32 idClient)
{

}

void Players::keyLeft(qint32 idClient)
{

}

void Players::keyUp(qint32 idClient)
{

}

void Players::keyDown(qint32 idClient)
{

}

void Players::keySpace(qint32 idClient)
{

}

/* INFOS */
bool Players::playerAvailable() const
{
    DEBUG("Players::playerAvailable() count:" << this->size() << " max:" << _maxPlayers, false);
    return this->size() < _maxPlayers;
}

bool Players::contains(qint32 idClient) const
{
    for (const QSharedPointer<Player> &player : *this)
    {
        if (player->idClient() == idClient)
            return true;
    }

    return false;
}
