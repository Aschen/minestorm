#ifndef MESSAGESCORE_HH
# define MESSAGESCORE_HH

# include <QTextStream>

# include <cassert>

# include "MessageBase.hh"

class MessageScore : public MessageBase
{
private:
    quint32         _score;

public:
    MessageScore(const QString &msg);
    MessageScore(MessageBase::Type type, QTextStream &stream);
    MessageScore(quint32 score);

    quint32         score() const;
};

#endif // MESSAGESCORE_HH
