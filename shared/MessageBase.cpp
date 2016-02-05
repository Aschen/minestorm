#include "MessageBase.hh"

MessageBase::MessageBase(Type type, const QString &messageString)
    : _type(type),
      _messageString(messageString)
{
}

MessageBase::~MessageBase()
{
}

MessageBase::Type MessageBase::type() const
{
    return _type;
}

const QString &MessageBase::messageString() const
{
    return _messageString;
}

MessageBase::Type MessageBase::getMessageType(const QString &msg)
{
    QTextStream         stream(msg.toUtf8());
    qint32              type;

    stream >> type;
    return (MessageBase::Type) type;
}
