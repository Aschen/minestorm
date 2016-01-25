#ifndef GAMEPROXY_HH
# define GAMEPROXY_HH

# include <QObject>

# include "Minestorm.hh"
# include "Core.hh"
# include "Display.hh"

class GameProxy : public QObject
{
    Q_OBJECT

public:
    GameProxy(Core *core, Display *display);
    ~GameProxy();

//public slots:
//    void                mousePressed(int x, int y);
//    void                mouseReleased(int x, int y);
//    void                mouseMoved(int x, int y);
//    void                keyPressed(int key);
//    void                keyReleased(int key);

//signals:
//    void                sigMousePressed(int x, int y);
//    void                sigMouseReleased(int x, int y);
//    void                sigMouseMoved(int x, int y);
//    void                sigKeyPressed(int key);
//    void                sigKeyReleased(int key);

};

#endif // GAMEPROXY_HH
