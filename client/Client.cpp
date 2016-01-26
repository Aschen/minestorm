#include "Client.hh"

Client::Client(const QString &ip, quint16 port)
    : _ip(ip),
      _port(port),
      _blockSize(0)
{
    connect(&_clientSocket, SIGNAL(readyRead()),
            this,           SLOT(receiveMessage()));
    connect(&_clientSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,           SLOT(displayError(QAbstractSocket::SocketError)));
}

Client::~Client()
{
}

void Client::connectServer()
{
    _blockSize = 0;
    _clientSocket.abort();
    _clientSocket.connectToHost(_ip, _port);
}

void Client::receiveMessage()
{
    QDataStream     in(&_clientSocket);

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
    qDebug() << "Received : " << message;
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
    qDebug() << _clientSocket.errorString();
}

