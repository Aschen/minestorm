#include "Client.hh"

Client::Client(const QString &ip, quint16 port, QObject *parent)
    : QObject(parent),
      _ip(ip),
      _port(port),
      _socket(-1)
{
    qDebug() << "Client::Client()";

    // For tests
    connect(this,       SIGNAL(sigSendMessage(qint32, const QString&)),
            &_socket,   SLOT(sendMessage(qint32, const QString&)));
    connect(&_socket,   SIGNAL(receiveMessage(qint32,QString)),
            this,       SLOT(receiveMessage(qint32,QString)));
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
    emit sigSendMessage(BaseSocket::BROADCAST, msg);
}

const BaseSocket *Client::socket() const
{
    return &_socket;
}

void Client::receiveMessage(qint32 socketFd, const QString &msg)
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
















