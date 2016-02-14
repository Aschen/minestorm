#include "MessagePlayersInfos.hh"

/* type players_count player_number pseudo lives score */
MessagePlayersInfos::MessagePlayersInfos(const QString &msg, PlayersInfos *playersInfos)
    : MessageBase(MessageBase::ERROR, msg),
      _playersInfos(playersInfos)
{
    QTextStream     stream(msg.toUtf8());
    qint32          type;
    quint32         playersCount;
    quint32         number;
    QString         pseudo;
    quint32         lives;
    quint32         score;

    /* Read type */
    stream >> type;
    _type = (MessageBase::Type) type;
    assert(type == MessageBase::PLAYERS_INFOS);

    /* Read players count */
    stream >> playersCount;

    /* Read each players infos */
    for (quint32 i = 0; i < playersCount; ++i)
    {
        /* player_number pseudo lives score */
        stream >> number >> pseudo >> lives >> score;

        if (!_playersInfos->contains(number))
        {
            _playersInfos->addPlayer(number);
        }
        _playersInfos->setPlayerLives(number, lives);
        _playersInfos->setPlayerScore(number, score);
        _playersInfos->setPlayerPseudo(number, pseudo);
    }
}


/* type players_count player_number pseudo lives score */
MessagePlayersInfos::MessagePlayersInfos(const Players &players)
    : MessageBase(MessageBase::PLAYERS_INFOS, ""),
      _playersInfos(nullptr)
{
    /* Write message type */
    _messageString = QString::number((qint32) _type) + " ";

    /* Write players count */
    _messageString += QString::number((qint32) players.count()) + " ";

    DEBUG("MessagePlayersInfos::MessagePlayersInfos() players:" << players.size (), false);
    /* Write each player */
    for (const QSharedPointer<Player> &player : players)
    {
        /* Write player_number */
        _messageString += QString::number(player->number()) + " ";

        /* Write pseudo */
        _messageString += player->pseudo() + " ";

        /* Write lives */
        _messageString += QString::number(player->lives()) + " ";

        /* Write score */
        _messageString += QString::number(player->score()) + " ";
    }
    DEBUG("MessagePlayersInfos::MessagePlayersInfos() : " << _messageString, false);
}
