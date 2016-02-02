#include "Client.hh"

Client::Client(const QString &ip, quint16 port, QObject *parent)
    : QObject(parent),
      _ip(ip),
      _port(port),
      _socket(-1)
{
    DEBUG("Client::Client()", true);

    /* Quand la socket reçoit un message,
    ** on l'envoi au message dispatcher qui emet le signal
    ** pour le display correspondant au message reçu
    */
    connect(&_socket,   SIGNAL(receiveMessage(qint32, QString)),
            this,       SLOT(messageDispatcher(qint32, QString)));
}

Client::~Client()
{
    DEBUG("Client::~Client()", true);
}

void Client::start()
{
    if (!_socket.isValid())
    {
        DEBUG("Client::start() : Connect to " << _ip << ":" << _port, true);
        _socket.connectToHost(_ip, _port);
    }
    else
    {
        DEBUG("Client::start() : Error, already connected", true);
    }
}

void Client::stop()
{
    if (_socket.isValid())
    {
        DEBUG("Client::stop() : Stop connection", true);
        // Need to reset _msgSize when stop socket
        _socket.abort();
    }
    else
    {
        DEBUG("Client::stop() : Error, not connected", true);
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

        DEBUG("Client::MessageDispatcher() : Receive " << message.objects()->size() << " objects", false);
        emit receiveInfoObjects(message.objects());
    }
    else
    {
        DEBUG(msg, true);
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
















