#ifndef WORKER_HH
# define WORKER_HH

# include <QThread>
# include <QTcpSocket>
# include <QByteArray>
# include <QDataStream>
# include <QChar>
# include <QDebug>

class Worker : public QThread
{
    Q_OBJECT

private:
    int             _socketFd;
    quint16         _msgSize;
    QTcpSocket      *_socket;

public:
    Worker(int socketFd, QObject *parent = nullptr);
    ~Worker();

    int             socketFd() const;

    // QThread interface
protected:
    void            run() Q_DECL_OVERRIDE;

private:
    QByteArray      getMessage(const QString &msg);

signals:
    void            error(QTcpSocket::SocketError socketError);
    // Emit signal when the full message is received from client connected to worker
    void            receiveMessage(int socketFd, const QString &msg);

public slots:
    // Received disconnected() signal from the socket
    void            disconnected();
    // Read bytes on socket and emit receiveMessage() when full message arrived
    void            readMessage();
    // Server emit signal to send message to client connected to worker
    void            sendMessage(const QString &msg);
    // Receive error from the socket
    void            displayError(QAbstractSocket::SocketError socketError);

};

#endif // WORKER_HH
