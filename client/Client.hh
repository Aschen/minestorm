#ifndef CLIENT_HH
# define CLIENT_HH

# include <QTextStream>
# include <QSharedPointer>
# include <QVector>
# include <QPolygon>

# include "Minestorm.hh"
# include "MessageObjects.hh"
# include "BaseSocket.hh"

class Client : public QObject
{
    Q_OBJECT

private:
    QString             _ip;
    quint16             _port;
    BaseSocket          _socket;

public:
    Client(const QString &ip, quint16 port, QObject *parent = nullptr);
    ~Client();

    void                start();
    void                stop();

    void                sendMessage(const QString &msg);

    const BaseSocket    *socket() const;

signals:
    void                transfertMessage(qint32 socketFd, const QString &msg);

public slots:
    void                receiveMessage(qint32 socketFd, const QString &msg);
};

#endif // CLIENT_HH
