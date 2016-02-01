#include "BaseSocket.hh"

BaseSocket::BaseSocket(qint32 socketFd, QObject *parent)
    : QTcpSocket(parent),
      _socketFd(socketFd),
      _msgSize(0)
{
    qDebug() << "BaseSocket::BaseSocket() : " << socketFd;
    connect(this, SIGNAL(readyRead()),
            this, SLOT(readMessage()), Qt::DirectConnection);
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)), Qt::DirectConnection);
}

BaseSocket::~BaseSocket()
{
}

QByteArray BaseSocket::packMessage(const QString &msg) const
{
    QByteArray  block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16) 0;
    out << msg;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    return  block;
}

qint32 BaseSocket::fd() const
{
    return _socketFd;
}

void BaseSocket::readMessage()
{
    QDataStream     in(this);

    //qDebug() << "BaseSocket::readMessage() ";
    in.setVersion(QDataStream::Qt_4_0);

    // If it's a whole new message
    if (_msgSize == 0)
    {
        if (bytesAvailable() < (qint32) sizeof(quint16))
        {
            qDebug() << "BaseSocket::readMessage() : Error, to few bytes availables (< sizeof(quint16) )";
            return;
        }

        // Read message size
        in >> _msgSize;
    }

    // If the full message isn't arrived, return and wait for more bytes
    if (bytesAvailable() < _msgSize)
    {
        qDebug() << "BaseSocket::readMessage() : Error, too few bytes availables (< _msgSize)";
        return;
    }

    QString         message;

    in >> message;
    emit receiveMessage(_socketFd, message);
    //qDebug() << "BaseSocket::readMessage() : Full message readed : " << message;

    // Prepare to read whole new message
    _msgSize = 0;
}

void BaseSocket::sendMessage(qint32 socketFd, const QString &msg)
{
    if (socketFd == _socketFd || socketFd == BROADCAST)
    {
        qDebug() << "BaseSocket::sendMessage() " << _socketFd << " : " << msg;
        write(packMessage(msg));
    }
}

void BaseSocket::displayError(QAbstractSocket::SocketError socketError)
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
    qDebug() << "BaseSocket::displayError() : " << errorString();
   // emit disconnected();
}
