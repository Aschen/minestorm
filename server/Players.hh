#ifndef PLAYERS_HH
# define PLAYERS_HH

# include <QList>
# include <QPoint>
# include <QSharedPointer>

# include "Player.hh"

# include <cassert>

using PlayersList = QList<QSharedPointer<Player>>;

class Players : public PlayersList
{
private:
    const qint32            _maxPlayers;
    QVector<QPoint>         _spawns;

public:
    Players(qint32 maxPlayers = MAX_PLAYERS);

    QSharedPointer<Entity>  &newPlayer(qint32 idClient);
    void                    deletePlayer(qint32 idClient);

    /* Events */
    void                    keyRight(qint32 idClient);
    void                    keyLeft(qint32 idClient);
    void                    keyUp(qint32 idClient);
    void                    keyDown(qint32 idClient);
    QSharedPointer<Entity>  keySpace(qint32 idClient);

    bool                    playerAvailable() const;
    bool                    contains(qint32 idClient) const;
    QSharedPointer<Player>  &findPlayer(qint32 idClient);

private:
};

#endif // PLAYERS_HH
