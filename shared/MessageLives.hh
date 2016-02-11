#ifndef MESSAGELIVES_HH
# define MESSAGELIVES_HH

# include <QTextStream>

# include <cassert>

# include "MessageBase.hh"

class MessageLives : public MessageBase
{
private:
    quint32         _lives;

public:
    MessageLives(const QString &msg);
    MessageLives(MessageBase::Type type, QTextStream &stream);
    MessageLives(quint32 score);

    quint32         lives() const;
};

#endif // MESSAGELIVE_HH
