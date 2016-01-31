#include "GameProxy.hh"

GameProxy::GameProxy(Core *core, Display *display) :
    QObject(nullptr)
{
    connect(display, SIGNAL(sigMousePressed(int,int)), core, SLOT(mousePressed(int,int)));
    connect(display, SIGNAL(sigMouseReleased(int,int)), core, SLOT(mouseReleased(int,int)));
    connect(display, SIGNAL(sigMouseMoved(int,int)), core, SLOT(mouseMoved(int,int)));
    connect(display, SIGNAL(sigStart(QSize)), core, SLOT(start(QSize)));
    connect(display, SIGNAL(sigPause()), core, SLOT(pause()));
    connect(display, SIGNAL(sigReset()), core, SLOT(reset()));
    connect(display, SIGNAL(sigTest()), core, SLOT(test()));

    connect(core, SIGNAL(sendObjects(const QVector<QPolygon>&)), display, SLOT(receiveObjects(const QVector<QPolygon>&)));
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

