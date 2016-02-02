#ifndef CLIENT_HH
# define CLIENT_HH

# include <QTcpSocket>
# include <QDataStream>
# include <QByteArray>
# include <QTextStream>
# include <QDebug>
# include <QSharedPointer>
# include <QVector>
# include <QPolygon>

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

public slots:
    void                messageDispatcher(qint32 socketFd, const QString &msg);

signals:
    void                receiveInfoObjects(const QSharedPointer<QVector<QPolygon>> &objects);
};

#endif // CLIENT_HH
