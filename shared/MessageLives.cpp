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

    /* Read playerNumber + lives */
    stream >> _playerNumber >> _lives;
}

MessageLives::MessageLives(MessageBase::Type type, QTextStream &stream)
    : MessageBase(type, *(stream.string()))
{
    stream  >> _playerNumber>> _lives;
}

/* type player_number lives */
MessageLives::MessageLives(quint32 playerNumber, quint32 lives)
    : MessageBase(MessageBase::LIVES, "")
{
    DEBUG("MessageLives::MessageLives() : lives" << lives << " for player" << playerNumber, true);
    _messageString = QString::number((qint32) _type) + " ";
    _messageString += QString::number(playerNumber) + " ";
    _messageString += QString::number(lives) + " ";
}

quint32 MessageLives::lives() const
{
    return _lives;
}

quint32 MessageLives::playerNumber() const
{
    return _playerNumber;
}
