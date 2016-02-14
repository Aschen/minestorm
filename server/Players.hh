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
    void                    keyPressRight(qint32 idClient);
    void                    keyPressLeft(qint32 idClient);
    void                    keyPressUp(qint32 idClient);
    void                    keyPressDown(qint32 idClient);
    QSharedPointer<Entity>  keyPressSpace(qint32 idClient);
    void                    keyReleaseRight(qint32 idClient);
    void                    keyReleaseLeft(qint32 idClient);
    void                    keyReleaseUp(qint32 idClient);
    void                    keyReleaseSpace(qint32 idClient);
    void                    playerPseudo(qint32 idClient, const QString &pseudo);

    bool                    playerAvailable() const;
    bool                    contains(qint32 idClient) const;
    QSharedPointer<Player>  &findPlayer(qint32 idClient);

private:
};

#endif // PLAYERS_HH
