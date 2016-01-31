#ifndef CORE_HH
# define CORE_HH

# include <QObject>
# include <QTimer>
# include <QPoint>
# include <QVector>
# include <QPolygon>
# include <QString>
# include <QTextStream>

# include <string>
# include <sstream>

# include "Minestorm.hh"
# include "Server.hh"
# include "Entity.hh"
# include "Carre.hh"

class Core : public QObject
{    
    Q_OBJECT

private:
    bool                _isRunning;
    const int           _cps;
    QTimer              _timer;
    int                 _step;
    Server              _server;
    EntityList          _entities;

public:
    Core(int cps);
    ~Core();

public slots:
    void                mousePressed(int x, int y);
    void                mouseReleased(int x, int y);
    void                mouseMoved(int x, int y);
    void                keyPressed(int key);
    void                keyReleased(int key);
    void                start();
    void                pause();
    void                reset();
    void                test();

private slots:
    void                step();
    void                messageDispatcher(qint32 socketFd, const QString &msg);

signals:
    void                sendObjects(const QVector<QPolygon> &objects);
};

#endif // CORE_HH
