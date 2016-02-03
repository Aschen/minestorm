#include "Display.hh"
#include "Ship.hh"

Display::Display(const QSize &size, qint32 fps, QObject *parent)
    : QObject(parent),
      _isRunning(false),
      _size(size),
      _fps(fps),
      _client(QSharedPointer<Client>(new Client)),
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

    connect(_client.data(), SIGNAL(transfertMessage(qint32, QString)),
            this,           SLOT(messageDispatcher(qint32,QString)));
}

/* *** */
void Display::draw(QPainter &painter, QRect &size)
{
    (void) size;
    DEBUG("Display::draw() : " << _objects->size() << " objects to draw", false);
    painter.fillRect(size, QColor(255,255,255));

    if (_objects != nullptr)
    {
        _objectsMutex.lock();
        for (Element &object : *_objects)
        {
            painter.setPen(QColor(object.imgId(), 0, 0));
            painter.setBrush(QBrush(QColor(object.imgId(), 0, 0)));
            painter.drawConvexPolygon(object.polygon());
        }
        _objectsMutex.unlock();
    }
}

void Display::startDisplay()
{
    _timer.start(1000 / _fps); // Répète le timer en fonction des fps
    _isRunning = true;
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
        receiveObjects(message.objects());
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
void Display::mousePressed(qint32 x, qint32 y)
{
    DEBUG("Display::mousePressed() : x = " << x << ", y = " << y, true);

    MessageMouse    message(MessageBase::MOUSE_PRESSED, x, y);

    _client->sendMessage(message.messageString());
}

void Display::keyPressed(qint32 key)
{
    DEBUG("Display::keyPressed() : key =" << key, true);

    MessageKey    message(MessageBase::KEY_PRESSED, key);

    _client->sendMessage(message.messageString());
}

void Display::keyReleased(qint32 key)
{
    DEBUG("Display::keyReleased() : key =" << key, false);

//    MessageKey    message(MessageBase::KEY_RELEASED, key);

//    _client->sendMessage(message.messageString());
}

void Display::startNewGame()
{
    DEBUG("Display::startNewGame()", true);

    _client->start("localhost");
    startDisplay();
}

void Display::joinGame(const QString &host)
{
    DEBUG("Display::joinGame() : Join" << host, true);

    _client->start(host);
    startDisplay();
}

void Display::exitGame()
{
    DEBUG("Display::exitGame()", true);

    _client->stop();

    QApplication::quit();
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

const QVector<Element> &Display::objects() const
{
    return *_objects;
}

void Display::receiveObjects(const QSharedPointer<QVector<Element>> &objects)
{
    DEBUG("Display::receiveObjects() : " << objects->size() << " objects received", false);

    _objectsMutex.lock();
    _objects = objects;
    _objectsMutex.unlock();
}

void Display::update()
{
    if (_isRunning)
    {
        DEBUG("Display::Update()", false);
        emit changed();
    }
}
