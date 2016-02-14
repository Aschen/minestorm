#ifndef MESSAGEPLAYERINFOS_HH
# define MESSAGEPLAYERINFOS_HH

# include <QTextStream>

# include <cassert>

# include "MessageBase.hh"
# include "Players.hh"

class MessagePlayersInfos : public MessageBase
{
private:
    quint32         _playerNumber;
public:
    MessagePlayersInfos(const QString &msg);
    MessagePlayersInfos(MessageBase::Type type, QTextStream &stream);
    MessagePlayersInfos(const Players &players);


};

#endif // MESSAGEPLAYERINFOS_HH
