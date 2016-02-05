#include "MessageInfo.hh"

MessageInfo::MessageInfo(const QString &msg)
    : MessageBase(MessageBase::ERROR, msg)
{
    QTextStream     stream(msg.toUtf8());
    qint32          type;

    stream >> type;
    _type = (MessageBase::Type) type;
}

MessageInfo::MessageInfo(MessageBase::Type type)
    : MessageBase(type, "")
{
    _messageString = QString::number((qint32) type) + " ";
}

MessageInfo::~MessageInfo()
{

}
