#ifndef SERVER_HH
# define SERVER_HH

# include <QTcpServer>
# include <QNetworkInterface>

# include "Minestorm.hh"
# include "Worker.hh"

/**
 * @brief The Server class listen for new client and can receive or send message to any client
 */
class Server : public QTcpServer
{
    Q_OBJECT

private:
    quint16                     _port;
    QHostAddress                _address;
    quint32                     _clientCount;

public:
    Server(quint16 port, QObject *parent = nullptr);
    ~Server();

    void                        start();
    void                        broadcast(const QString &message);
    void                        unicast(qint32 idClient, const QString &message);

    quint32                     clientCount() const;

    // QTcpServer override
    void                        incomingConnection(qintptr socketFd) Q_DECL_OVERRIDE;

signals:
    void                        sendMessage(qint32 socketFd, const QString &msg);
    void                        transfertMessage(qint32 socketFd, const QString &msg);
    void                        clientConnected(qint32 sockedFd);
    void                        sigClientDisconnected(qint32 socketFd);

public slots:
    void                        clientDisconnected(qint32 socketFd);
    void                        receiveMessage(qint32 socketFd, const QString &msg);
};

#endif // SERVER_HH
