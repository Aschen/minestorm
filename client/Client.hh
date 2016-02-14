#ifndef CLIENT_HH
# define CLIENT_HH

# include <QTextStream>
# include <QSharedPointer>
# include <QVector>
# include <QPolygon>

# include <cassert>

# include "Minestorm.hh"
# include "BaseSocket.hh"

class Client : public QObject
{
    Q_OBJECT

public:
    enum Type
    {
        PLAYER      = 1,
        SPECTATOR   = 2
    };


private:
    QString             _host;
    quint16             _port;
    BaseSocket          _socket;
    Type                _type;

public:
    Client(const QString &host, quint16 port, QObject *parent = nullptr);
    Client(QObject *parent = nullptr);
    ~Client();

    bool                start();
    bool                start(const QString &host);
    void                stop();

    void                sendMessage(const QString &msg);

    void                type(Client::Type type);
    const BaseSocket    *socket() const;
    void                hostname(const QString &host);
    void                port(quint16 port);

signals:
    void                transfertMessage(qint32 socketFd, const QString &msg);

public slots:
    void                receiveMessage(qint32 socketFd, const QString &msg);
};

#endif // CLIENT_HH
