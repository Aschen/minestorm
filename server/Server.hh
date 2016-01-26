#ifndef SERVER_HH
# define SERVER_HH

# include <QTcpServer>
# include <QTcpSocket>
# include <QHash>
# include <QDataStream>
# include <QByteArray>

# include <iostream>

class Server : public QTcpServer
{
    Q_OBJECT

private:
    quint16                         _port;
    QHostAddress                    _address;
    QHash<QString, QTcpSocket>      _clients;

public:
    Server(quint16 port);
    ~Server();

    void                            start();

private slots:
    void                            sendMessage();

private:
    QByteArray                      getMessage(const QString &message);
};

#endif // SERVER_HH
