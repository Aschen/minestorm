#ifndef MESSAGEPLAYERINFOS_HH
# define MESSAGEPLAYERINFOS_HH

# include <QTextStream>

# include <cassert>

# include "MessageBase.hh"
# include "Players.hh"
# include "PlayersInfos.hh"

class MessagePlayersInfos : public MessageBase
{
private:
    PlayersInfos    *_playersInfos;

public:
    MessagePlayersInfos(const QString &msg, PlayersInfos *playersInfos);
    MessagePlayersInfos(const Players &players);


};

#endif // MESSAGEPLAYERINFOS_HH
