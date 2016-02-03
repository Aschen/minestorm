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
# include "Carre.hh"
# include "MessageFactory.hpp"


class Core : public QObject
{    
    Q_OBJECT

private:
    bool                _isRunning;
    const qint32        _cps;
    QTimer              _timer;
    qint32              _step;
    Server              _server;
    EntityList          _entities;

public:
    Core(qint32 cps);
    ~Core();

    void                mousePressed(qint32 idClient, qint32 x, qint32 y);
    void                keyPressed(qint32 idClient, qint32 key);
    void                keyReleased(qint32 idClient, qint32 key);
    void                start();
    void                pause();
    void                reset();
    void                test();
    void                initialize(QSize size);

private slots:
    void                step();
    void                messageDispatcher(qint32 idClient, const QString &msg);
};

#endif // CORE_HH
