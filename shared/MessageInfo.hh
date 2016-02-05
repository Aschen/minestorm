#ifndef MESSAGEINFO_HH
# define MESSAGEINFO_HH

# include <QTextStream>

# include <cassert>

# include "MessageBase.hh"

class MessageInfo : public MessageBase
{
public:
    MessageInfo(const QString &msg);
    MessageInfo(MessageBase::Type type);
    ~MessageInfo();
};

#endif // MESSAGEINFO_HH
