#include "MessageLives.hh"

MessageLives::MessageLives(const QString &msg)
    : MessageBase(MessageBase::ERROR, msg)
{
    QTextStream     stream(msg.toUtf8());
    qint32          type;

    /* Read type */
    stream >> type;
    _type = (MessageBase::Type) type;
    assert(type == MessageBase::LIVES);

    /* Read lives */
    stream >> _lives;
}

MessageLives::MessageLives(MessageBase::Type type, QTextStream &stream)
    : MessageBase(type, *(stream.string()))
{
    stream >> _lives;
}

MessageLives::MessageLives(quint32 lives)
    : MessageBase(MessageBase::LIVES, "")
{
    _messageString = QString::number((qint32) _type) + " ";
    _messageString += QString::number(lives) + " ";
}

quint32 MessageLives::lives() const
{
    return _lives;
}
