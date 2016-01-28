#include "Worker.hh"

Worker::Worker(qint32 socketFd, QObject *parent)
    : QThread(parent),
      _socket(socketFd, parent)
{
    qDebug() << "Worker::Worker() " << _socket.fd();
    connect(&_socket,   SIGNAL(disconnected()),
            this,       SLOT(disconnected()));
}

Worker::~Worker()
{
    qDebug() << "Worker::~Worker() " << _socket.fd();
}

qint32 Worker::socketFd() const
{
    return _socket.fd();
}

const BaseSocket *Worker::socket() const
{
    return &_socket;
}

void Worker::disconnected()
{
    qDebug() << "Worker::disconnected()";
    exit(0);
}

void Worker::run()
{
    qDebug() << "Worker::run() " << _socket.fd();

    if (!_socket.setSocketDescriptor(_socket.fd()))
    {
//        emit error(_socket.error());
        qDebug() << "Error on worker" << _socket.error();
        return; // Exit thread
    }

    exec();
}
