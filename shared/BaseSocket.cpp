#include "BaseSocket.hh"

BaseSocket::BaseSocket(qint32 socketFd, QObject *parent)
    : QTcpSocket(parent),
      _socketFd(socketFd),
      _msgSize(0)
{
    DEBUG("BaseSocket::BaseSocket() : " << socketFd, false);
    connect(this, SIGNAL(readyRead()),
            this, SLOT(readMessage()), Qt::DirectConnection);
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)), Qt::DirectConnection);
}

BaseSocket::~BaseSocket()
{
    DEBUG("BaseSocket::~BaseSocket()", true);
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

/* PRIVATE SLOT */
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
            DEBUG("BaseSocket::readMessage() : Error : Malformed frame)", false);
            return;
        }

        // Read message size
        in >> _msgSize;
    }

    // If the full message isn't arrived, return and wait for more bytes
    if (bytesAvailable() < _msgSize)
    {
        return;
    }

    QString         message;

    in >> message;
    DEBUG("BaseSocket::readMessage() : Full message readed : " << message, false);
    emit receiveMessage(_socketFd, message);

    // Prepare to read whole new message
    _msgSize = 0;
}

/* PUBLIC SLOT */
void BaseSocket::sendMessage(qint32 socketFd, const QString &msg)
{

    DEBUG("BaseSocket::sendMessage() :" << _socketFd << socketFd, false);
    if (isOpen() && (socketFd == _socketFd || socketFd == BROADCAST))
    {
        DEBUG("BaseSocket::sendMessage() " << _socketFd << " : " << msg, false);
        write(packMessage(msg));
        this->waitForBytesWritten();
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
    DEBUG("BaseSocket::displayError() : " << errorString(), false);
   // emit disconnected();
}
