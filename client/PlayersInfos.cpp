#include "PlayersInfos.hh"

PlayersInfos::PlayersInfos()
    : _positions(MAX_PLAYERS)
{
    quint32     padding = 30;
    quint32     textSize = 80;

    _positions[0] = QPoint(padding, padding);
    _positions[1] = QPoint(SCREEN_WIDTH - textSize, padding);
    _positions[2] = QPoint(SCREEN_WIDTH - textSize, SCREEN_HEIGHT - padding - 30);
    _positions[3] = QPoint(padding, SCREEN_HEIGHT - padding - 30);
}

void PlayersInfos::addPlayer(quint32 playerNumber)
{
    if (this->size() < MAX_PLAYERS)
    {
        DEBUG("PlayersInfos::addPlayer() playerNumber" << playerNumber, false);
        this->push_back(QSharedPointer<PlayerInfos>(
                            new PlayerInfos(playerNumber, _positions[playerNumber - 1])));
    }
}

void PlayersInfos::removePlayer(quint32 playerNumber)
{
    for (auto it = this->begin(); it != this->end(); ++it)
    {
        if ((*it)->number() == playerNumber)
        {
            this->erase(it);
            break;
        }
    }
}

bool PlayersInfos::contains(quint32 playerNumber) const
{
    for (const QSharedPointer<PlayerInfos> &player : *this)
    {
        if (player->number() == playerNumber)
            return true;
    }
    return false;
}

QSharedPointer<PlayerInfos> &PlayersInfos::findPlayer(quint32 playerNumber)
{
    for (QSharedPointer<PlayerInfos> &player : *this)
    {
        if (player->number() == playerNumber)
            return player;
    }
    assert(false);
}

void PlayersInfos::setPlayerScore(quint32 playerNumber, quint32 score)
{
    findPlayer(playerNumber)->score(score);
}

void PlayersInfos::setPlayerLives(quint32 playerNumber, quint32 lives)
{
    findPlayer(playerNumber)->lives(lives);
}

void PlayersInfos::setPlayerPseudo(quint32 playerNumber, const QString &pseudo)
{
    findPlayer(playerNumber)->pseudo(pseudo);
}

