#include "Client.hh"

Client::Client(const QString &ip, quint16 port, QObject *parent)
    : QObject(parent),
      _ip(ip),
      _port(port),
      _blockSize(0)
{
    qDebug() << "Client::Client()";
    connect(&_clientSocket, SIGNAL(readyRead()),
            this,           SLOT(receiveMessage()));
    connect(&_clientSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,           SLOT(displayError(QAbstractSocket::SocketError)));
}

Client::~Client()
{
    qDebug() << "Client::~Client()";
}

void Client::connectServer()
{
    qDebug() << "Client::connectServer() : " << _ip << ":" << _port;
    _blockSize = 0;
    _clientSocket.abort();
    _clientSocket.connectToHost(_ip, _port);
}

void Client::receiveMessage()
{
    QDataStream     in(&_clientSocket);

    qDebug() << "Client::receiveMessage()";
    in.setVersion(QDataStream::Qt_4_0);

    if (_blockSize == 0)
    {
        if (_clientSocket.bytesAvailable() < (int) sizeof(quint16))
        {
            qDebug() << "To few bytes availables (< sizeof(quint16) )";
            return;
        }

        in >> _blockSize;
    }

    if (_clientSocket.bytesAvailable() < _blockSize)
    {
        qDebug() << "Too few bytes availables (< _blockSize)";
        return;
    }

    QString         message;

    in >> message;
    qDebug() << "Client::receiveMessage() : " << message;
    _blockSize = 0;
}

void Client::displayError(QAbstractSocket::SocketError socketError)
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
    qDebug() << "Client::displayError() : " << _clientSocket.errorString();
}

