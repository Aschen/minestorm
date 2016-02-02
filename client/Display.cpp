#include "Display.hh"

Display::Display(const QSize &size, int fps, QObject *parent)
    : QObject(parent),
      _isRunning(false),
      _size(size),
      _fps(fps),
      _client("127.0.0.1", 4242),
      _objects(nullptr)
{
    DEBUG("Display::Display()", true);
    _timer.setSingleShot(false);
    /* Le signal timeout() est envoyé toutes les 40ms,
    ** on le connecte à la fonction Display::update()
    ** qui fait appel à GameBoard::paintEvent()
    ** qui fait appel à Display::draw()
    */
    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));

    connect(&_client,   SIGNAL(transfertMessage(qint32, QString)),
            this,       SLOT(messageDispatcher(qint32,QString)));
}

/* *** */
void Display::draw(QPainter &painter, QRect &size)
{
    (void) size;
    DEBUG("Display::draw() : " << _objects->size() << " objects to draw", false);
    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(QBrush(QColor(0, 0, 0)));

    if (_objects != nullptr)
    {
        _objectsMutex.lock();
        for (auto object : *_objects)
        {
            painter.drawConvexPolygon(object);
        }
        _objectsMutex.unlock();
    }
}

void Display::initialize()
{
}

void Display::start()
{
    DEBUG("Display::start()", false);
    _timer.start(1000 / _fps); // Répète le timer en fonction des fps
    _isRunning = true;
    _client.start();
    emit sigStart();
}

void Display::pause()
{
    DEBUG("Display::pause()", false);
    _timer.stop();
    _isRunning = false;
    emit sigPause();
}

void Display::reset()
{
    DEBUG("Display::reset()", false);
    pause();
    initialize();
    emit changed();
    emit sigReset();
}

void Display::test()
{
    DEBUG("Display::test()", false);

    emit sigTest();
}

void Display::update()
{
    DEBUG("Display::update()", false);
    if (_isRunning)
    {
        emit changed();
    }
}

void Display::messageDispatcher(qint32 socketFd, const QString &msg)
{
    (void) socketFd;
    DEBUG("Display::messageDispatcher() :" << msg, false);

    MessageBase::Type       msgType = MessageBase::getMessageType(msg);

    switch (msgType)
    {
    case MessageBase::INFO_OBJECTS:
    {
        MessageObjects      message(msg);

        DEBUG("Client::MessageDispatcher() : Receive " << message.objects()->size() << " objects", false);
        receiveObjects (message.objects());
        break;
    }
    default:
    {
        DEBUG("Display::messageDispatcher() : Unknown message" << msg, true);
        break;
    }
    }
}


/* EVENTS */
void Display::mousePressed(int x, int y)
{
    DEBUG("Display::mousePressed() : x = " << x << ", y = " << y, true);
    _client.sendMessage("1 " + QString::number(x) + " " + QString::number(y));
    emit sigMousePressed(x, y);
}

void Display::mouseReleased(int x, int y)
{
    emit sigMouseReleased(x, y);
}

void Display::mouseMoved(int x, int y)
{
    emit sigMouseMoved(x, y);
}

void Display::keyPressed(int key)
{
    emit sigKeyPressed(key);
}

void Display::keyReleased(int key)
{
    emit sigKeyReleased(key);
}

/* GETTERS/SETTERS */

const QSize &Display::size() const
{
    return _size;
}

bool Display::isRunning() const
{
    return _isRunning;
}

const QVector<QPolygon> &Display::objects() const
{
    return *_objects;
}

void Display::receiveObjects(const QSharedPointer<QVector<QPolygon>> &objects)
{
    DEBUG("Display::receiveObjects() : " << objects->size() << " objects received", false);
    _objectsMutex.lock();
    _objects = objects;
    _objectsMutex.unlock();
}
