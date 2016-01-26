#ifndef CLIENT_HH
# define CLIENT_HH

# include <QTcpSocket>
# include <QDataStream>
# include <QByteArray>
# include <QDebug>

# include <iostream>

class Client : public QObject
{
    Q_OBJECT

private:
    QString         _ip;
    quint16         _port;
    quint16         _blockSize;
    QTcpSocket      _clientSocket;

public:
    Client(const QString  &ip, quint16 port);
    ~Client();

    void            connectServer();

private slots:
    void            receiveMessage();
    void            displayError(QAbstractSocket::SocketError socketError);

};

#endif // CLIENT_HH
