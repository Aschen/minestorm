#ifndef CORE_HH
# define CORE_HH

# include <QObject>
# include <QTimer>
# include <QPoint>

# include <string>

# include "DrawableObject.hh"
# include "Minestorm.hh"
# include "Entity.hh"

class Core : public QObject
{    
    Q_OBJECT

private:
    bool                _isRunning;
    const int           _cps;
    QTimer              _timer;
    int                 _step;
    //    DrawableObjectMap   _friendly;
    //    DrawableObjectMap   _mines;
    DrawableObjectMap   _objects;
    DrawableObjectList  _objectsList;
    EntityList          _entities;

public:
    Core(int cps);

    bool                addObject(const DrawableObject &object);
    bool                removeObject(const std::string &name);
    bool                removeObject(const DrawableObject &object);

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

signals:
    void                sendObjects(const DrawableObjectList &objects);
};

#endif // CORE_HH
