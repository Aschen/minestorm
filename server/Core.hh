#ifndef CORE_HH
# define CORE_HH

# include <QObject>
# include <QTimer>
# include <QPoint>
# include <QVector>
# include <QPolygon>
# include <QString>
# include <QTextStream>

# include "Minestorm.hh"
# include "Server.hh"
# include "Entity.hh"
# include "Ship.hh"
# include "MessageMouse.hh"
# include "MessageInfo.hh"
# include "MessageKey.hh"
# include "MessageObjects.hh"
# include "MessageFactory.hpp"
# include "Collision.hh"


class Core : public QObject
{    
    Q_OBJECT

private:
    bool                _isRunning;
    const qint32        _cps;
    QTimer              _timer;
    qint32              _step;
    Server              _server;
    quint32             _playersCount;
    EntityHash          _entitiesMap;

public:
    Core(qint32 cps = CYCLE_PER_S);
    ~Core();

    void                mousePressed(qint32 idClient, qint32 x, qint32 y);
    void                keyPressed(qint32 idClient, qint32 key);
    void                keyReleased(qint32 idClient, qint32 key);
    void                startGame();


private:
    void                entitiesMovement();

private slots:
    void                step();
    void                messageDispatcher(qint32 idClient, const QString &msg);
    void                newPlayer(qint32 idClient);
    void                playerLeft(qint32 idClient);
};

#endif // CORE_HH
