#include "Client.hh"

Client::Client(const QString &ip, quint16 port, QObject *parent)
    : QObject(parent),
      _ip(ip),
      _port(port),
      _socket(-1, parent)
{
    qDebug() << "Client::Client()";

    // For tests
    connect(this, SIGNAL(sigSendMsg(QString)), &_socket, SLOT(sendMessage(QString)));
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

void Client::sendMessageFunction(const QString &msg)
{
    emit sigSendMsg(msg);
}
