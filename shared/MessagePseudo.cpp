#include "MessagePseudo.hh"

MessagePseudo::MessagePseudo(const QString &msg)
    : MessageBase(MessageBase::ERROR, msg)
{
    QTextStream     stream(msg.toUtf8());
    qint32          type;

    /* Read type */
    stream >> type;
    _type = (MessageBase::Type) type;
    assert(type == MessageBase::PSEUDO);

    /* Read pseudo */
    stream >> _pseudo;
}

/* type pseudo */
MessagePseudo::MessagePseudo(MessageBase::Type type, const QString &pseudo)
    : MessageBase(type, "")
{
    /* Write message type */
    _messageString = QString::number((qint32) _type) + " ";

    /* Write pseudo */
    _messageString += pseudo + " ";
}

const QString &MessagePseudo::pseudo() const
{
    return _pseudo;
}
