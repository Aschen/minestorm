#include "Players.hh"

Players::Players(quint32 maxPlayers)
    : _maxPlayers(maxPlayers),
      _playersCount(0)
{
    initPlayers();
}

void Players::initPlayers()
{
    qint32      screenPart = SCREEN_SIZE / 4;


    this->push_back(QSharedPointer<Player>(new Player(1, QPoint(1 * screenPart, 1 * screenPart))));
    this->push_back(QSharedPointer<Player>(new Player(2, QPoint(3 * screenPart, 1 * screenPart))));
    this->push_back(QSharedPointer<Player>(new Player(3, QPoint(3 * screenPart, 3 * screenPart))));
    this->push_back(QSharedPointer<Player>(new Player(4, QPoint(1 * screenPart, 3 * screenPart))));
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

QSharedPointer<Player> &Players::findAvailable()
{
    assert(this->playerAvailable());
    for (QSharedPointer<Player> &player : *this)
    {
        if (player->available())
            return player;
    }
    assert(false);
}

QSharedPointer<Player> Players::get(quint32 i)
{
    return this->operator[](i);
}

quint32 Players::count() const
{
    return _playersCount;
}

QSharedPointer<Entity> &Players::newPlayer(qint32 idClient)
{
    assert(this->playerAvailable());
    DEBUG("Players::newPlayer() idClient:" << idClient, true);

    QSharedPointer<Player>  &player = findAvailable();

    _playersCount++;
    return player->newPlayer(idClient);
}

void Players::deletePlayer(qint32 idClient)
{
    QSharedPointer<Player>  &player = findPlayer(idClient);

    _playersCount--;
    player->playerLeft();
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
    DEBUG("Players::playerAvailable() count:" << _playersCount << " max:" << _maxPlayers, true);
    return _playersCount < _maxPlayers;
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
