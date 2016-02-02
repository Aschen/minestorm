#include "Server.hh"

Server::Server(quint16 port, QObject *parent)
    : QTcpServer(parent),
      _port(port),
      _address(QHostAddress::Any)
{
    DEBUG("Server::Server()", true);

    _timer.setSingleShot(false);
//    _timer.start(1000/ 20);
    _count = 0;
   // connect(&_timer, SIGNAL(timeout()), this, SLOT(broadcast()));
    //QTimer::singleShot(3000, this, SLOT(broadcast()));
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
    qDebug() << "Server::incomingConnection() : New connection " << socketFd;

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

    worker->start();
}

void Server::broadcast(const QString &message)
{
    //qDebug() << "Server::broadcast()";

    emit sendMessage(BaseSocket::BROADCAST, message);
}

void Server::receiveMessage(qint32 socketFd, const QString &msg)
{
    qDebug() << "Server::receiveMessage() : Worker " << socketFd << msg;
    emit transfertMessage(socketFd, msg);
}
