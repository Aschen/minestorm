#include "Server.hh"

Server::Server(quint16 port, QObject *parent)
    : QTcpServer(parent),
      _port(port),
      _address(QHostAddress::Any),
      _clientCount(0)
{
    DEBUG("Server::Server()", false);
}

Server::~Server()
{
    DEBUG("Server::~Server()", true);
}

void Server::start()
{
    if (!isListening())
    {
        if (!listen(_address, _port))
        {
            DEBUG("Server error listen", true);
        }
        else
        {
            foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
            {
                if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
                {
                    DEBUG("Server::start() : Listening on" << address.toString() << ":" << _port, true);
                }
            }
        }
    }
}

void Server::incomingConnection(qintptr socketFd)
{
    DEBUG("Server::incomingConnection() : New connection " << socketFd, true);

    _clientCount++;

    // Create worker to handle the new connection
    Worker  *worker = new Worker(socketFd);

    // When thread exit(), call deleteLater to destroy QObject which is a pointer here
    connect(worker, SIGNAL(finished()),
            worker, SLOT(deleteLater()));

    // Connect communications functions for each worker
    connect(this,               SIGNAL(sendMessage(qint32, const QString&)),
            worker->socket(),   SLOT(sendMessage(qint32, const QString&)));
    connect(worker->socket(),   SIGNAL(receiveMessage(qint32, const QString&)),
            this,               SLOT(receiveMessage(qint32, const QString&)));
    connect(worker,             SIGNAL(clientDisconnected(qint32)),
            this,               SLOT(clientDisconnected(qint32)));

    emit clientConnected(worker->socketFd());

    worker->start();
}

void Server::clientDisconnected(qint32 socketFd)
{
    DEBUG("Server::clientDisconnected() : Client" << socketFd, true);

    _clientCount--;
    emit sigClientDisconnected(socketFd);
}

void Server::broadcast(const QString &message)
{
    DEBUG("Server::broadcast()", false);

    emit sendMessage(BaseSocket::BROADCAST, message);
}

void Server::unicast(qint32 idClient, const QString &message)
{
    DEBUG("Server::unicast() : Client:" << idClient << " message:" << message, false);

    emit sendMessage(idClient, message);
}

quint32 Server::clientCount() const
{
    return _clientCount;
}

void Server::receiveMessage(qint32 socketFd, const QString &msg)
{
    DEBUG("Server::receiveMessage() : Worker " << socketFd << msg, false);
    emit transfertMessage(socketFd, msg);
}
