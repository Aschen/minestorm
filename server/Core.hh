#ifndef CORE_HH
# define CORE_HH

# include <QObject>
# include <QTimer>
# include <QPoint>
# include <QVector>
# include <QPolygon>

# include <string>

# include "Minestorm.hh"
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
    EntityList          _entities;

public:
    Core(int cps);

public slots:
    void                mousePressed(int x, int y);
    void                mouseReleased(int x, int y);
    void                mouseMoved(int x, int y);
    void                keyPressed(int key);
    void                keyReleased(int key);
    void                start(QSize size);
    void                pause();
    void                reset();
    void                test();
    void                initialize(QSize size);

private slots:
    void                step();

signals:
    void                sendObjects(const QVector<QPolygon> &objects);
};

#endif // CORE_HH
