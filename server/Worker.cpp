#include "Worker.hh"

Worker::Worker(int socketFd, QObject *parent)
    : QThread(parent),
      _socketFd(socketFd)
{
    qDebug() << "Worker::Worker() " << _socketFd;
}

Worker::~Worker()
{
    qDebug() << "Worker::~Worker() " << _socketFd;
}

int Worker::socketFd() const
{
    return _socketFd;
}

void Worker::run()
{
    qDebug() << "Worker::run() " << _socketFd;

    _socket = new QTcpSocket;

    if (!_socket->setSocketDescriptor(_socketFd))
    {
        emit error(_socket->error());
        qDebug() << "Error on worker" << _socket->error();
        return; // Exit thread
    }

    connect(_socket, SIGNAL(readyRead()),
            this,    SLOT(readyRead()), Qt::DirectConnection);
    connect(_socket, SIGNAL(disconnected()),
            this,    SLOT(disconnected()));

    exec();
}

QByteArray Worker::getMessage(const QString &message)
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

void Worker::readyRead()
{
    QByteArray  data = _socket->readAll();

    qDebug() << "Worker::readyRead() " << _socketFd << " : " << data;

    emit receiveMessage(_socketFd, data);
}

void Worker::disconnected()
{
    qDebug() << "Worker::disconnected() " << _socketFd;

    _socket->deleteLater();

    exit(0);
}

void Worker::sendMessage(const QByteArray &msg)
{
    qDebug() << "Worker::sendMessage() " << _socketFd << " : " << msg;
    _socket->write(msg);
}
