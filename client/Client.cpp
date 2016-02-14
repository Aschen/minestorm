#include "Client.hh"

Client::Client(const QString &host, quint16 port, QObject *parent)
    : QObject(parent),
      _host(host),
      _port(port),
      _socket(BaseSocket::BROADCAST),
      _type(PLAYER)
{
    DEBUG("Client::Client()", false);

    connect(&_socket,   SIGNAL(receiveMessage(qint32, QString)),
            this,       SLOT(receiveMessage(qint32, QString)));
}

Client::Client(QObject *parent)
    : QObject(parent),
      _host(""),
      _port(SERVER_PORT),
      _socket(BaseSocket::BROADCAST),
      _type(PLAYER)
{
    DEBUG("Client::Client()", false);
    connect(&_socket,   SIGNAL(receiveMessage(qint32, QString)),
            this,       SLOT(receiveMessage(qint32, QString)));
}

Client::~Client()
{
    DEBUG("Client::~Client()", true);
}

bool Client::start()
{
    assert(_host != "");

    if (!_socket.isValid())
    {
        _socket.connectToHost(_host, _port);
        if (!_socket.isOpen())
        {
            DEBUG("Client::start() : Unable to connect to" << _host << _port << " :" << _socket.errorString(), true);
            return false;
        }
        else
        {
            DEBUG("Client::start() : Connected to " << _host << ":" << _port, true);
            return true;
        }
    }

    return false;
}

bool Client::start(const QString &host)
{
    _host = host;

    return start();
}

void Client::stop()
{
    if (_socket.isOpen())
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

void Client::sendMessage( const QString &msg)
{
    if (_type == PLAYER)
        _socket.sendMessage(BaseSocket::BROADCAST, msg);
}

void Client::type(Client::Type type)
{
    _type = type;
}

const BaseSocket *Client::socket() const
{
    return &_socket;
}

void Client::hostname(const QString &host)
{
    _host = host;
}

void Client::port(quint16 port)
{
    _port = port;
}

void Client::receiveMessage(qint32 socketFd, const QString &msg)
{
    DEBUG("Client::receiveMessage() :" << msg, false);
    emit transfertMessage(socketFd, msg);
}
















