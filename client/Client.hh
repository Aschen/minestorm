#ifndef CLIENT_HH
# define CLIENT_HH

# include <QTcpSocket>
# include <QDataStream>
# include <QByteArray>
# include <QDebug>

# include "BaseSocket.hh"

class Client : public QObject
{
    Q_OBJECT

private:
    QString         _ip;
    quint16         _port;
    BaseSocket      _socket;

public:
    Client(const QString  &ip, quint16 port, QObject *parent = nullptr);
    ~Client();

    void            start();
    void            stop();

    void            sendMessageFunction(const QString &msg);

signals:
    // For tests
    void            sigSendMsg(qint32 socketFd, const QString &msg);
};

#endif // CLIENT_HH
