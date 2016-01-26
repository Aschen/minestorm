#include "Worker.hh"

Worker::Worker(int socketFd, QObject *parent)
    : QThread(parent),
      _socketFd(socketFd),
      _msgSize(0)
{
    qDebug() << "Worker::Worker() " << _socketFd;
    connect(_socket, SIGNAL(readyRead()),
            this,    SLOT(readMessage()));
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

    _socket = new QTcpSocket; // Useless pointer ?

    if (!_socket->setSocketDescriptor(_socketFd))
    {
        emit error(_socket->error());
        qDebug() << "Error on worker" << _socket->error();
        return; // Exit thread
    }

    connect(_socket, SIGNAL(readyRead()),
            this,    SLOT(readMessage()), Qt::DirectConnection);
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,     SLOT(displayError(QAbstractSocket::SocketError)), Qt::DirectConnection);

    connect(_socket, SIGNAL(disconnected()),
            this,    SLOT(disconnected()));

    exec();
}

QByteArray Worker::getMessage(const QString &msg)
{
    QByteArray  block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16) 0;
    out << msg;
    out.device()->seek(0);
    out <<(quint16) (block.size() - sizeof(quint16));

    return  block;
}

void Worker::disconnected()
{
    qDebug() << "Worker::disconnected() " << _socketFd;

    _socket->deleteLater();

    exit(0);
}

void Worker::readMessage()
{
    QDataStream     in(_socket);

    qDebug() << "Worker::readMessage()";
    in.setVersion(QDataStream::Qt_4_0);

    // If it's a whole new message
    if (_msgSize == 0)
    {
        if (_socket->bytesAvailable() < (int) sizeof(quint16))
        {
            qDebug() << "Worker::readMessage() : Error, to few bytes availables (< sizeof(quint16) )";
            return;
        }

        // Read message size
        in >> _msgSize;
    }

    // If the full message isn't arrived, return and wait for more bytes
    if (_socket->bytesAvailable() < _msgSize)
    {
        qDebug() << "Worker::readMessage() : Error, too few bytes availables (< _msgSize)";
        return;
    }

    QString         message;

    in >> message;
    emit receiveMessage(_socketFd, message);
    qDebug() << "Worker::readMessage() : Message readed : " << message;

    // Prepare to read whole new message
    _msgSize = 0;
}

void Worker::sendMessage(const QString &msg)
{
    qDebug() << "Worker::sendMessage() " << _socketFd << " : " << msg;
    _socket->write(getMessage(msg));
}

void Worker::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            break;
        case QAbstractSocket::ConnectionRefusedError:
            break;
        default:
            break;
        }
    qDebug() << "Worker::displayError() : " << _socket->errorString();
}
