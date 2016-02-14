#ifndef MESSAGEPSEUDO_HH
#define MESSAGEPSEUDO_HH

# include <QTextStream>

# include <cassert>

# include "MessageBase.hh"

class MessagePseudo : public MessageBase
{
private:
    QString         _pseudo;

public:
    MessagePseudo(const QString &msg);
    MessagePseudo(MessageBase::Type type, const QString &pseudo);

    const QString   &pseudo() const;
};

#endif // MESSAGEPSEUDO_HH
