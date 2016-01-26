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
    QTcpSocket      *_socket;

public:
    Worker(int socketFd, QObject *parent = nullptr);
    ~Worker();

    int             socketFd() const;

    // QThread interface
protected:
    void            run() Q_DECL_OVERRIDE;

private:
    QByteArray      getMessage(const QString &message);

signals:
    void            error(QTcpSocket::SocketError socketError);
    // Emit signal when receive message from client connected to worker
    void            receiveMessage(int socketFd, const QByteArray &msg);

public slots:
    void            readyRead();
    void            disconnected();
    // Server emit signal to send message to client connected to worker
    void            sendMessage(const QByteArray &msg);
};

#endif // WORKER_HH
