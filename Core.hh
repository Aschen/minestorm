#ifndef CORE_HH
# define CORE_HH

# include <QObject>

# include "DrawableObject.hh"
# include "Minestorm.hh"

class Core : public QObject
{    
    Q_OBJECT

private:
    DrawableObjectMap   _objects;
    DrawableObjectList  _objectsList;

public:
    Core();

    bool                addObject(const DrawableObject &object);
    bool                removeObject(const std::string &name);
    bool                removeObject(const DrawableObject &object);

public slots:
    void                mousePressed(int x, int y);
    void                mouseReleased(int x, int y);
    void                mouseMoved(int x, int y);
    void                keyPressed(int key);
    void                keyReleased(int key);

signals:
    void                sendObjects(const DrawableObjectList &objects);
};

#endif // CORE_HH
