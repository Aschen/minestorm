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

QString MessageBase::typeStr() const
{
    return MessageBase::STRINGS[_type];
}

const QHash<MessageBase::Type, QString> MessageBase::STRINGS = {
    { MessageBase::ERROR, "ERROR" },
    { MessageBase::MOUSE_PRESSED, "MOUSE_PRESSED" },
    { MessageBase::MOUSE_RELEASED, "MOUSE_RELEASED" },
    { MessageBase::KEY_PRESSED, "KEY_PRESSED" },
    { MessageBase::KEY_RELEASED, "KEY_RELEASED" },
    { MessageBase::INFO_START, "INFO_START" },
    { MessageBase::INFO_STOP, "INFO_STOP" },
    { MessageBase::INFO_OBJECTS, "INFO_OBJECTS" }
};
