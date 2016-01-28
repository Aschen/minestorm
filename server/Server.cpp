#include "Server.hh"

Server::Server(quint16 port, QObject *parent)
    : QTcpServer(parent),
      _port(port),
      _address(QHostAddress::Any)
{
    qDebug() << "Server::Server()";
    _timer.setSingleShot(false);
//    _timer.start(1000/ 20);
    _count = 0;
    connect(&_timer, SIGNAL(timeout()), this, SLOT(broadcast()));
    //QTimer::singleShot(3000, this, SLOT(broadcast()));
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
    connect(this,               SIGNAL(sendMessage(qint32, const QString&)),
            worker->socket(),   SLOT(sendMessage(qint32, const QString&)));
    connect(worker->socket(),   SIGNAL(receiveMessage(qint32, const QString&)),
            this,               SLOT(receiveMessage(qint32, const QString&)));

    worker->start();
}

void Server::broadcast()
{
    qDebug() << "Server::broadcast()";
    QString message("12,15;18,19;18,45;23,69;125,652;458,215;125,545;654,452;654,856;215,122;545,212;541,558;152,452;213,645;452,145;545,455;545,578;524,545;487,669;321,645;666,555;222,333;222,888;444,555;999,666;555,444;777,454;552,154;218,895;224,236632,422;598,812;451,255;454,777;444,555;666,999;555,444;888,222;333,222;555,666;546,123;966,784;545,425;875,545;554,545;541,254;546,312;254,251;855,145;212,545;221,512;658,456;254,456;545,521;512,854;256,521;96,32;54,81;91,81;51,21");

    emit sendMessage(BaseSocket::BROADCAST, message);
}

void Server::receiveMessage(qint32 socketFd, const QString &msg)
{
    qDebug() << "Server::receiveMessage() : Worker " << socketFd << msg;
    emit transfertMessage(socketFd, msg);
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

