#include "Client.hh"

Client::Client(const QString &ip, quint16 port, QObject *parent)
    : QObject(parent),
      _ip(ip),
      _port(port),
      _socket(-1)
{
    DEBUG("Client::Client()", true);

    connect(&_socket,   SIGNAL(receiveMessage(qint32, QString)),
            this,       SLOT(receiveMessage(qint32, QString)));
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

void Client::receiveMessage(qint32 socketFd, const QString &msg)
{
    DEBUG("Client::receiveMessage() :" << msg, false);
    emit transfertMessage(socketFd, msg);
}
















