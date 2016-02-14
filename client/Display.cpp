#include "Display.hh"
#include "Ship.hh"



Display::Display(const QSize &size, QObject *parent)
    : QObject(parent),
      _isRunning(false),
      _size(size),
      _client(QSharedPointer<Client>(new Client)),
      _elements(nullptr)
{
    DEBUG("Display::Display()", false);

    connect(_client.data(), SIGNAL(transfertMessage(qint32, QString)),
            this,           SLOT(messageDispatcher(qint32,QString)));
}

void Display::draw(QPainter &painter, QRect &size)
{
    (void) size;
    QTransform t;
    QTransform tInv;
    DEBUG("Display::draw() : " << _elements->size() << " elements to draw", false);

    /* Draw elements */
    if (_elements != nullptr)
    {
        for (const Element &element : *_elements)
        {
            DEBUG("Display:draw() : element.type() = " << element.type(), false);
            element.draw(painter, _images);
        }
    }

    /* Draw players infos*/
    for (const QSharedPointer<PlayerInfos> &playerInfos : _playersInfos)
    {
        playerInfos->draw(painter, _images);
    }

    /* Draw FPS */
    _fpsCounter.draw(painter, _images);
    _fpsCounter.frameDraw();
}

void Display::messageDispatcher(qint32 socketFd, const QString &msg)
{
    (void) socketFd;
    DEBUG("Display::messageDispatcher() :" << msg, false);

    MessageBase::Type       msgType = MessageBase::getMessageType(msg);

    switch (msgType)
    {
    case MessageBase::OBJECTS:
    {
        MessageObjects      message(msg);
        receiveObjects(message.elements());
        break;
    }
    case MessageBase::PLAYERS_INFOS:
    {
        MessagePlayersInfos message(msg, &_playersInfos);

        if (_isRunning)
            emit changed();
        break;
    }
    default:
    {
        DEBUG("Display::messageDispatcher() : Unknown message" << msg, true);
        break;
    }
    }
}

void Display::receiveObjects(const QSharedPointer<QVector<Element>> &elements)
{
    DEBUG("Display::receiveObjects() : " << elements->size() << " elements received", false);

    _elements = elements;

    if (_isRunning)
        emit changed();
}

/* EVENTS */
void Display::mousePressed(qint32 x, qint32 y)
{
    DEBUG("Display::mousePressed() : x = " << x << ", y = " << y, false);

    MessageMouse    message(MessageBase::MOUSE_PRESSED, x, y);

    if (_isRunning)
        _client->sendMessage(message.messageString());
}

void Display::keyPressed(qint32 key)
{
    DEBUG("Display::keyPressed() : key =" << key, false);

    MessageKey    message(MessageBase::KEY_PRESSED, key);

    if (_isRunning)
        _client->sendMessage(message.messageString());
}

void Display::keyReleased(qint32 key)
{
    DEBUG("Display::keyReleased() : key =" << key, false);

    /* Key echap is only for Client */
    if (key == Qt::Key_Escape)
    {
        DEBUG("Display::keyPressed() : Echap", true);
        stopGame();
        return ;
    }

    MessageKey    message(MessageBase::KEY_RELEASE, key);

    if (_isRunning)
        _client->sendMessage(message.messageString());
}

void Display::startDisplay()
{
    _isRunning = true;
    _fpsCounter.start();
}

void Display::stopDisplay()
{
    _isRunning = false;
    _fpsCounter.stop();
}

void Display::startNewGame()
{
    DEBUG("Display::startNewGame()", true);

    _client->start("localhost");
    startDisplay();
}

void Display::joinGame(const QString &host, const QString &pseudo)
{
    if (!_isRunning)
    {
        MessagePseudo       message(MessageBase::PSEUDO, pseudo);

        DEBUG("Display::joinGame() : Join" << host, false);
        /* Start client (socket) */
        _client->start(host);

        /* Send pseudo to Server */
        _client->sendMessage(message.messageString ());

        /* Start display */
        startDisplay();
    }
}

void Display::exitGame()
{
    DEBUG("Display::exitGame()", true);

    _client->stop();

    QApplication::quit();
}

void Display::stopGame()
{
    if (_isRunning)
    {
        _elements.clear();
        _playersInfos.clear();

        emit changed ();
        _client->stop();
        stopDisplay();
    }
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

const QVector<Element> &Display::elements() const
{
    return *_elements;
}
