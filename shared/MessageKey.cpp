#include "MessageKey.hh"

MessageKey::MessageKey(const QString &msg)
    : MessageBase(MessageBase::ERROR, msg)
{
    QTextStream     stream(msg.toUtf8());
    qint32          type;

    stream >> type;
    _type = (MessageBase::Type) type;
    createKeyCode(stream);
}

MessageKey::MessageKey(MessageBase::Type type, QTextStream &stream)
    : MessageBase(type, *(stream.string()))
{
    createKeyCode(stream);
}

MessageKey::MessageKey(MessageBase::Type type, qint32 keyCode)
    : MessageBase(type, "")
{
    _messageString = QString::number((qint32) type) + " ";
    _messageString += QString::number(keyCode) + " ";
}

MessageKey::~MessageKey()
{
}

qint32 MessageKey::keyCode() const
{
    return _keyCode;
}

void MessageKey::createKeyCode(QTextStream &stream)
{
    assert(_type == MessageBase::KEY_PRESSED || _type == MessageBase::KEY_RELEASE);

    stream >> _keyCode;
}
