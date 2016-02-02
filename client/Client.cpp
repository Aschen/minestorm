#include "Client.hh"

Client::Client(const QString &ip, quint16 port, QObject *parent)
    : QObject(parent),
      _ip(ip),
      _port(port),
      _socket(-1)
{
    qDebug() << "Client::Client()";

    /* Quand la socket reçoit un message,
    ** on l'envoi au message dispatcher qui emet le signal
    ** pour le display correspondant au message reçu
    */
    connect(&_socket,   SIGNAL(receiveMessage(qint32, QString)),
            this,       SLOT(messageDispatcher(qint32, QString)));
}

Client::~Client()
{
    qDebug() << "Client::~Client()";
}

void Client::start()
{
    if (!_socket.isValid())
    {
        qDebug() << "Client::start() : Connect to " << _ip << ":" << _port;
        _socket.connectToHost(_ip, _port);
    }
    else
    {
        qDebug() << "Client::start() : Error, already connected";
    }
}

void Client::stop()
{
    if (_socket.isValid())
    {
        qDebug() << "Client::stop() : Stop connection";
        // Need to reset _msgSize when stop socket
        _socket.abort();
    }
    else
    {
        qDebug() << "Client::stop() : Error, not connected";
    }
}

void Client::sendMessage(const QString &msg)
{
    _socket.sendMessage(BaseSocket::BROADCAST, msg);
}

const BaseSocket *Client::socket() const
{
    return &_socket;
}

void Client::messageDispatcher(qint32 socketFd, const QString &msg)
{
    (void) socketFd;

    QTextStream     stream(msg.toUtf8());
    qint32          type;
    MessageBase::Type   msgType;

    stream >> type;
    msgType = (MessageBase::Type) type;

    if (msgType == MessageBase::INFO_OBJECTS)
    {
        MessageObjects      message(msg);

        qDebug() << "Receive " << message.objects()->size() << " objects";
        emit receiveInfoObjects(message.objects());
    }
    else
    {
        qDebug() << msg;
    }

//    switch (msgType)
//    {
//    case MessageBase::INFO_OBJECTS:
//        MessageObjects      message(msg);
//        emit receiveInfoObjects(message.objects());
//        break;

//    default:
//        break;
//    }
}
















