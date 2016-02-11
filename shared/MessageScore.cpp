#include "MessageScore.hh"

MessageScore::MessageScore(const QString &msg)
    : MessageBase(MessageBase::ERROR, msg)
{
    QTextStream     stream(msg.toUtf8());
    qint32          type;

    /* Read type */
    stream >> type;
    _type = (MessageBase::Type) type;
    assert(type == MessageBase::SCORE);

    /* Read score */
    stream >> _score;
}

MessageScore::MessageScore(MessageBase::Type type, QTextStream &stream)
    : MessageBase(type, *(stream.string()))
{
    stream >> _score;
}

MessageScore::MessageScore(quint32 score)
    : MessageBase(MessageBase::SCORE, "")
{
    _messageString = QString::number((qint32) _type) + " ";
    _messageString += QString::number(score) + " ";
}

quint32 MessageScore::score() const
{
    return _score;
}
