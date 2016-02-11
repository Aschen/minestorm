#include "Display.hh"
#include "Ship.hh"


Display::Display(const QSize &size, QObject *parent)
    : QObject(parent),
      _isRunning(false),
      _size(size),
      _client(QSharedPointer<Client>(new Client)),
      _elements(nullptr){
    DEBUG("Display::Display()", true);

    connect(_client.data(), SIGNAL(transfertMessage(qint32, QString)),
            this,           SLOT(messageDispatcher(qint32,QString)));
}

void Display::draw(QPainter &painter, QRect &size)
{
    DEBUG("Display::draw() : " << _elements->size() << " elements to draw", false);
    if (_elements != nullptr)
    {
        for (const Element &element : *_elements)
        {
            DEBUG("Display:draw() : element.type() = " << element.type(), false);
            switch (element.type())
            {
            case Element::MINE_S:
            case Element::MINE_L:
            case Element::MINE_M:
                painter.drawImage(element.center(), _images.getImage(element.type()));
                break;
            case Element::SHIP_1:
            case Element::SHIP_2:
            case Element::SHIP_3:
            case Element::SHIP_4:
                /*  IF SHIELD
                 * if(element.shild) { ... }
                */
                painter.setBrush(QBrush("#98F5FF"));
                painter.setPen(QColor("#98F5FF"));
                painter.drawEllipse(element.center(), SHIP_SIZE / 2, SHIP_SIZE / 2);

                painter.setPen(QColor("#AAAAAA"));
                painter.setBrush(QBrush(Qt::NoBrush));
                painter.drawConvexPolygon(element.polygon());
                painter.drawPoint(element.center());
                painter.drawImage(element.imageCenter(), _images.getImage(element.type(), element.angle()));

                break;
            case Element::SHOT:
                painter.setPen(QColor(255, 0, 51)); // RED
                painter.setBrush(QBrush(Qt::NoBrush));
                painter.drawConvexPolygon(element.polygon());
                break;
            }
        }
    }

    /* Draw score */
    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(QBrush(QColor(0, 0, 0)));
    painter.drawText(QPoint(SCREEN_SIZE - 50, 10), _score);

    /* Draw lives */
    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(QBrush(QColor(0, 0, 0)));
    painter.drawText(QPoint(SCREEN_SIZE - 50, 20), _lives);

}

void Display::startDisplay()
{
    _isRunning = true;
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
    case MessageBase::SCORE:
    {
        MessageScore        message(msg);
        receiveScore(message.score());
        break;
    }
    case MessageBase::LIVES:
    {
        MessageLives        message(msg);
        receiveLives(message.lives());
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

void Display::receiveScore(quint32 score)
{
    DEBUG("Client::receiveScore() : Receive score " << score, true);

    _score = QString::number(score);

    if (_isRunning)
        emit changed();
}

void Display::receiveLives(quint32 lives)
{
    DEBUG("Client::receiveLives() : Receive lives " << lives, true);

    _lives = QString("Vies: ") + QString::number(lives);

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

const QVector<Element> &Display::elements() const
{
    return *_elements;
}
