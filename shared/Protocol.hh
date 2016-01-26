#ifndef PROTOCOL_HH
# define PROTOCOL_HH

# include <QByteArray>
# include <QDataStream>

class Protocol
{
public:
    static QByteArray packMessage(const QString &msg);
};


#endif // PROTOCOL_HH
