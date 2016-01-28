#ifndef BASESOCKET_HH
# define BASESOCKET_HH

# include <QByteArray>
# include <QDataStream>
# include <QTcpSocket>

/**
 * @class BaseSocket
 * @brief Represent a socket endpoint connected to an other throught network
 *
 */
class BaseSocket : public QTcpSocket
{
    Q_OBJECT

public:
    enum Destination
    {
        BROADCAST = -1
    };

protected:
    const qint32    _socketFd; /**< Socket descriptor (or socker ID) */
    quint16         _msgSize;  /**< Current message size*/

public:
    BaseSocket(qint32 socketFd, QObject *parent = nullptr);
    virtual ~BaseSocket();

    QByteArray      packMessage(const QString &msg) const;

    qint32          fd() const;

signals:
    /**
     * @brief receiveMessage is emited when a full message is available on socket
     * @param socketFd The socket descriptor
     * @param msg The message as a QString
     */
    void            receiveMessage(qint32 socketFd, const QString &msg);

public slots:
    /**
     * @brief sendMessage Emit a signal on this slot to send a message throught socket
     * @param msg The message
     */
    void            sendMessage(qint32 socketFd, const QString &msg);

private slots:
    /**
     * @brief readMessage read bytes from socket and emit receiveMessage() when full message arrived
     */
    void            readMessage();
    /**
     * @brief displayError receive errors messages from the socket
     * @param socketError contain the error message
     */
    void            displayError(QAbstractSocket::SocketError socketError);

};


#endif // BASESOCKET_HH
