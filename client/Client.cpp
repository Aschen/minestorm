#include "Client.hh"

Client::Client(const QString &ip, quint16 port, QObject *parent)
    : QObject(parent),
      _ip(ip),
      _port(port),
      _msgSize(0)
{
    qDebug() << "Client::Client()";
    connect(&_socket, SIGNAL(readyRead()),
            this,     SLOT(readMessage()));
    connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,     SLOT(displayError(QAbstractSocket::SocketError)));

    // For tests
    connect(this, SIGNAL(sigSendMsg(QString)), this, SLOT(sendMessage(QString)));
}

Client::~Client()
{
    qDebug() << "Client::~Client()";
}

void Client::start()
{
    if (!_socket.isValid())
    {
        qDebug() << "Client::start() : Connect to " << _ip << ":" << _port;
        _socket.connectToHost(_ip, _port);
    }
    else
    {
        qDebug() << "Client::start() : Error, already connected";
    }
}

void Client::stop()
{
    if (_socket.isValid())
    {
        qDebug() << "Client::stop() : Stop connection";
        _msgSize = 0;
        _socket.abort();
    }
    else
    {
        qDebug() << "Client::stop() : Error, not connected";
    }
}

void Client::sendMessageFunction(const QString &msg)
{
    emit sigSendMsg(msg);
}

QByteArray Client::getMessage(const QString &msg)
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

void Client::readMessage()
{
    QDataStream     in(&_socket);

    qDebug() << "Client::readMessage()";
    in.setVersion(QDataStream::Qt_4_0);

    // If it's a whole new message
    if (_msgSize == 0)
    {
        if (_socket.bytesAvailable() < (int) sizeof(quint16))
        {
            qDebug() << "Client::readMessage() : Error, to few bytes availables (< sizeof(quint16) )";
            return;
        }

        // Read message size
        in >> _msgSize;
    }

    // If the full message isn't arrived, return and wait for more bytes
    if (_socket.bytesAvailable() < _msgSize)
    {
        qDebug() << "Client::readMessage() : Error, too few bytes availables (< _msgSize)";
        return;
    }

    QString         message;

    in >> message;
    emit receiveMessage(message);
    qDebug() << "Client::readMessage() : Message readed : " << message;

    // Prepare to read whole new message
    _msgSize = 0;
}

void Client::sendMessage(const QString &msg)
{
    qDebug() << "Client::sendMessage() : Send " << msg;
    _socket.write(getMessage(msg));
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            stop();
            break;
        case QAbstractSocket::HostNotFoundError:
            break;
        case QAbstractSocket::ConnectionRefusedError:
            break;
        default:
            break;
        }
    qDebug() << "Client::displayError() : " << _socket.errorString();
}

