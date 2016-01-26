#include "Server.hh"

Server::Server(quint16 port)
    : _port(port),
      _address(QHostAddress::Any)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(sendMessage()));
}

Server::~Server()
{
}

void Server::start()
{
    if (!isListening())
    {
        if (!listen(_address, _port))
        {
            std::cout << "Server error listen" << std::endl;
        }
        else
        {
            std::cout << "Server start listening on " << _port << std::endl;
        }
    }
}

void Server::sendMessage()
{
    QTcpSocket  *clientSocket = nextPendingConnection();
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));

    clientSocket->write(getMessage("Hello from server"));
    clientSocket->disconnectFromHost();
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

