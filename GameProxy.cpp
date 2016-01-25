#include "GameProxy.hh"

GameProxy::GameProxy(Core *core, Display *display) :
    QObject(nullptr)
{
    connect(display, SIGNAL(sigMousePressed(int,int)), core, SLOT(mousePressed(int,int)));
    connect(core, SIGNAL(sendObjects(DrawableObjectList)), display, SLOT(receiveObjects(DrawableObjectList)));
}

GameProxy::~GameProxy()
{
}

//void GameProxy::mousePressed(int x, int y)
//{
//    shared_ptr<DrawableObject>  rec = make_shared<DrawableObject>();

//    *rec << QPoint(x, y) << QPoint(x + 42, y) << QPoint(x + 42, y + 21) << QPoint(x, y + 42);
//    DEBUG("GameProxy::mousePressed : x = " << x << ", y = " << y);
//}

//void GameProxy::mouseReleased(int x, int y)
//{
//    DEBUG("GameProxy::mouseReleased : x = " << x << ", y = " << y);
//}

//void GameProxy::mouseMoved(int x, int y)
//{
//    DEBUG("GameProxy::mouseMoved : x = " << x << ", y = " << y);
//}

//void GameProxy::keyPressed(int key)
//{
//    DEBUG("GameProxy::keyPressed : key = " << key);
//}

//void GameProxy::keyReleased(int key)
//{
//    DEBUG("GameProxy::keyReleased : key = " << key);
//}

