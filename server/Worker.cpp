#include "Worker.hh"

Worker::Worker(qint32 socketFd, QObject *parent)
    : QThread(parent),
      _socket(socketFd, parent)
{
    DEBUG("Worker::Worker() " << _socket.fd(), false);
    connect(&_socket,   SIGNAL(disconnected()),
            this,       SLOT(disconnected()));
}

Worker::~Worker()
{
    DEBUG("Worker::~Worker() " << _socket.fd(), false);
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
    DEBUG("Worker::disconnected() : " << _socket.fd(), false);

    emit clientDisconnected(_socket.fd());
    exit(0);
}

void Worker::run()
{
    DEBUG("Worker::run() " << _socket.fd(), false);

    if (!_socket.setSocketDescriptor(_socket.fd()))
    {
//        emit error(_socket.error());
        DEBUG("Worker::run() : Error on worker " << _socket.fd() << _socket.error(), true);
        return;
    }

    exec();
}
