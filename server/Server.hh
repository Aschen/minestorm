#ifndef SERVER_HH
# define SERVER_HH

# include <QTcpServer>
# include <QSharedPointer>
# include <QTimer>
# include <QDebug>
# include <QFile> // REMOVE
# include <QByteArray> // REMOVE

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
    QTimer                      _timer;
    int _count;

public:
    Server(quint16 port, QObject *parent = nullptr);
    ~Server();

    void                        start();

    // QTcpServer override
    void                        incomingConnection(qintptr socketFd) Q_DECL_OVERRIDE;

signals:
    void                        sendMessage(qint32 socketFd, const QString &msg);
    void                        transfertMessage(qint32 socketFd, const QString &msg);

public slots:
    void                        broadcast(const QString &message);
    void                        receiveMessage(qint32 socketFd, const QString &msg);

private:
    QByteArray                  getMessage(const QString &message);
};

#endif // SERVER_HH
