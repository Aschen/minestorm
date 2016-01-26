#ifndef SERVER_HH
# define SERVER_HH

# include <QTcpServer>
# include <QTcpSocket>
# include <QDataStream>
# include <QByteArray>
# include <QDebug>
# include <QSharedPointer>
# include <QTimer>

# include "Worker.hh"

using namespace std;

class Server : public QTcpServer
{
    Q_OBJECT

private:
    quint16                     _port;
    QHostAddress                _address;
    QTimer                      _timer;

public:
    Server(quint16 port, QObject *parent = nullptr);
    ~Server();

    void                        start();

    // QTcpServer override
    void                        incomingConnection(qintptr socketFd) Q_DECL_OVERRIDE;

signals:
    void                        sendMessage(const QString &msg);

public slots:
    void                        broadcast();
    void                        receiveMessage(int socketFd, const QString &msg);

private:
    QByteArray                  getMessage(const QString &message);
};

#endif // SERVER_HH
