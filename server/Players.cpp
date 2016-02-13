#include "Players.hh"

Players::Players(quint32 maxPlayers)
    : _maxPlayers(maxPlayers)
{
}

void Players::initPlayers()
{
    qint32      screenPart = SCREEN_SIZE / 4;

    _players.push_back(QSharedPointer<Player>(new Player(1, QPoint(1 * screenPart, 1 * screenPart))));
    _players.push_back(QSharedPointer<Player>(new Player(2, QPoint(3 * screenPart, 1 * screenPart))));
    _players.push_back(QSharedPointer<Player>(new Player(3, QPoint(3 * screenPart, 3 * screenPart))));
    _players.push_back(QSharedPointer<Player>(new Player(4, QPoint(1 * screenPart, 3 * screenPart))));
}

QSharedPointer<Player> &Players::findPlayer(qint32 idClient)
{
    for (QSharedPointer<Player> &player : _players)
    {
        if (player->idClient() == idClient)
            return player;
    }
    assert(false);
}

quint32 Players::findAvailable() const
{
    quint32 index = -1;

    assert(this->playerAvailable());
    for (qint32 i = 0; i < _players.size(); ++i)
    {
        if (_players[i]->available())
        {
            index = i;
            break;
        }
    }

    return index;
}

quint32 Players::count() const
{
    quint32     availables = 0;

    for (const QSharedPointer<Player> &player : _players)
    {
        availables += player->available() ? 1 : 0;
    }

    return availables;
}

QSharedPointer<Entity> &Players::newPlayer(qint32 idClient)
{
    assert(this->playerAvailable());
    DEBUG("Players::newPlayer() idClient:" << idClient, true);

    quint32     index = findAvailable();

    _players[index]->newPlayer(idClient);
}

void Players::deletePlayer(qint32 idClient)
{

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
    return _playersCount < _maxPlayers;
}

bool Players::contains(qint32 idClient) const
{
    for (const QSharedPointer<Player> &player : _players)
    {
        if (player->idClient() == idClient)
            return true;
    }

    return false;
}
