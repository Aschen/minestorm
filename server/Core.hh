#ifndef CORE_HH
# define CORE_HH

# include <QObject>
# include <QTime>
# include <QTimer>
# include <QPoint>
# include <QVector>
# include <QPolygon>
# include <QString>
# include <QTextStream>

# include <algorithm>

# include "Minestorm.hh"
# include "Server.hh"
# include "Ship.hh"
# include "Mine.hh"
# include "Projectile.hh"
# include "MessageMouse.hh"
# include "MessageKey.hh"
# include "MessageObjects.hh"
# include "MessagePlayersInfos.hh"
# include "MessagePseudo.hh"
# include "Collision.hh"
# include "Players.hh"

class Core : public QObject
{    
    Q_OBJECT

private:
    bool                _isPlaying;
    const qint32        _cps;
    QTimer              _timer;
    qint32              _step;
    Server              _server;
    Players             _players;
    QList<qint32>       _spectators;
    EntitiesHash        _entities;

public:
    Core(qint32 cps);

    void                startGame();


private:
    // Events from messageDispatcher
    void                mousePressed(qint32 idClient, qint32 x, qint32 y);
    void                keyPressed(qint32 idClient, qint32 key);
    void                keyReleased(qint32 idClient, qint32 key);

    // Entities handles
    void                initMines();
    void                addMine(Mine::TypeMine type, quint32 x, quint32 y);
    void                addShip(QSharedPointer<Entity> &ship);
    void                addShot(QSharedPointer<Entity> shot);
    void                cleanEntities();

    void                sendPlayersInfos();
    void                sendObjects();

private slots:
    void                step();
    void                messageDispatcher(qint32 idClient, const QString &msg);
    void                clientJoin(qint32 idClient);
    void                clientLeft(qint32 idClient);
};

#endif // CORE_HH
