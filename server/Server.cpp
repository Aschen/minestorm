#include "Server.hh"

Server::Server(quint16 port, QObject *parent)
    : QTcpServer(parent),
      _port(port),
      _address(QHostAddress::Any)
{
    qDebug() << "Server::Server()";
    _timer.setSingleShot(false);
    _timer.start(1000);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(broadcast()));
}

Server::~Server()
{
    qDebug() << "Server::~Server()";
}

void Server::start()
{
    if (!isListening())
    {
        if (!listen(_address, _port))
        {
            qDebug() << "Server error listen";
        }
        else
        {
            qDebug() << "Server::start() : Listening on " << _port;
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

    // Connect communications functions
    connect(this,               SIGNAL(sendMessage(QString)),
            worker->socket(),   SLOT(sendMessage(QString)));
    connect(worker->socket(),   SIGNAL(receiveMessage(int, QString)),
            this,               SLOT(receiveMessage(int, QString)));

    worker->start();
}

void Server::broadcast()
{
    qDebug() << "Server::broadcast()";
    emit sendMessage("Hello dears clients");
}

void Server::receiveMessage(int socketFd, const QString &msg)
{
    qDebug() << "Server::receiveMessage() : Worker " << socketFd << msg;
}

QByteArray Server::getMessage(const QString &message)
{
    QByteArray  block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out <<(quint16) (block.size() - sizeof(quint16));

    return  block;
}

