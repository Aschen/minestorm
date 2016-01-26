#ifndef CLIENT_HH
# define CLIENT_HH

# include <QTcpSocket>
# include <QDataStream>
# include <QByteArray>
# include <QDebug>

# include "Protocol.hh"

class Client : public QObject
{
    Q_OBJECT

private:
    QString         _ip;
    quint16         _port;
    quint16         _msgSize;
    QTcpSocket      _socket;

public:
    Client(const QString  &ip, quint16 port, QObject *parent = nullptr);
    ~Client();

    void            start();
    void            stop();

    void            sendMessageFunction(const QString &msg);
    QByteArray      getMessage(const QString &msg);

signals:
    void            receiveMessage(const QString &msg);
    // For tests
    void            sigSendMsg(const QString &msg);

private slots:
    // Read bytes on socket and emit receiveMessage() when full message arrived
    void            readMessage();
    // Send message to the server connected to the client
    void            sendMessage(const QString &msg);
    void            displayError(QAbstractSocket::SocketError socketError);

};

#endif // CLIENT_HH
