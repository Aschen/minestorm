#include "Server.hh"

Server::Server(quint16 port, QObject *parent)
    : QTcpServer(parent),
      _port(port),
      _address(QHostAddress::Any),
      _clientCount(0)
{
    DEBUG("Server::Server()", true);
    _timer.setSingleShot(false);
//    _timer.start(1000/ 20);
//    QTimer::singleShot(3000, this, SLOT(broadcast()));
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
            DEBUG("Server::start() : Listening on " << _port, true);
        }
    }
}

void Server::incomingConnection(qintptr socketFd)
{
    DEBUG("Server::incomingConnection() : New connection " << socketFd, true);

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
    _clientCount++;
}

void Server::clientDisconnected(qint32 socketFd)
{
    DEBUG("Server::clientDisconnected() : Client" << socketFd, true);

    emit sigClientDisconnected(socketFd);
    _clientCount--;
}

void Server::broadcast(const QString &message)
{
    DEBUG("Server::broadcast()", false);

    emit sendMessage(BaseSocket::BROADCAST, message);
}

qint32 Server::clientCount() const
{
    return _clientCount;
}

void Server::receiveMessage(qint32 socketFd, const QString &msg)
{
    DEBUG("Server::receiveMessage() : Worker " << socketFd << msg, false);
    emit transfertMessage(socketFd, msg);
}
