#ifndef WORKER_HH
# define WORKER_HH

# include <QThread>
# include <QTcpSocket>
# include <QByteArray>
# include <QDataStream>
# include <QChar>
# include <QDebug>

# include "BaseSocket.hh"

class Worker : public QThread
{
    Q_OBJECT

private:
    BaseSocket          _socket;

public:
    Worker(int socketFd, QObject *parent = nullptr);
    ~Worker();

    int                 socketFd() const;

    const BaseSocket    *socket() const;

signals:
    void                receiveMessage(int socketFd, const QString &msg);

    // QThread interface
protected:
    void                run() Q_DECL_OVERRIDE;

};

#endif // WORKER_HH
