#ifndef MESSAGEKEY_HH
# define MESSAGEKEY_HH

# include <QTextStream>

# include <cassert>

# include "MessageBase.hh"

class MessageKey : public MessageBase
{
private:
    qint32          _keyCode;

public:
    MessageKey(const QString &msg);
    MessageKey(MessageBase::Type type, QTextStream &stream);
    MessageKey(MessageBase::Type type, qint32 keyCode);
    ~MessageKey();

    qint32          keyCode() const;

private:
    void            createKeyCode(QTextStream &stream);
};

#endif // MESSAGEKEY_HH
