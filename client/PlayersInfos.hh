#ifndef PLAYERSINFOS_HH
# define PLAYERSINFOS_HH

# include <cassert>

# include "Minestorm.hh"
# include "PlayerInfos.hh"

using PlayersInfosList = QList<QSharedPointer<PlayerInfos>>;

class PlayersInfos : public PlayersInfosList
{
private:
    QVector<QPoint>             _positions;

public:
    PlayersInfos();

    void                        addPlayer(quint32 playerNumber);
    void                        removePlayer(quint32 playerNumber);

    bool                        contains(quint32 playerNumber) const;
    QSharedPointer<PlayerInfos> &findPlayer(quint32 playerNumber);

    void                        setPlayerScore(quint32 playerNumber, quint32 score);
    void                        setPlayerLives(quint32 playerNumber, quint32 lives);
    void                        setPlayerPseudo(quint32 playerNumber, const QString &pseudo);
};

#endif // PLAYERS_HH
