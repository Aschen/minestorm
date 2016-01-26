#ifndef BASESOCKET_HH
# define BASESOCKET_HH

# include <QByteArray>
# include <QDataStream>
# include <QTcpSocket>


class BaseSocket : public QTcpSocket
{
    Q_OBJECT

protected:
    int             _socketFd; // Useless for client side
    quint16         _msgSize;

public:
    BaseSocket(int socketFd, QObject *parent = nullptr);
    virtual ~BaseSocket();

    QByteArray      packMessage(const QString &msg) const;

    int             fd() const;

signals:
    // Emit signal when the full message is received on socket
    void            receiveMessage(int socketFd, const QString &msg);

public slots:
    // Read bytes on socket and emit receiveMessage() when full message arrived
    void            readMessage();
    // Server emit signal to send message throught socket
    void            sendMessage(const QString &msg);
    // Receive error from the socket
    void            displayError(QAbstractSocket::SocketError socketError);

};


#endif // BASESOCKET_HH
