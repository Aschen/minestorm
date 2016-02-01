#include "MessageMouse.hh"

MessageMouse::MessageMouse(const QString &msg)
    : MessageBase(MessageBase::ERROR, msg)
{
    QTextStream     stream(msg.toUtf8());
    qint32          type;
    qint32          x;
    quint32         y;

    stream >> type >> x >> y;
    assert(type == MessageBase::MOUSE_PRESSED
           || type == MessageBase::MOUSE_RELEASED);

    _type = (MessageBase::Type) type;
    _point = QPoint(x, y);
}

MessageMouse::MessageMouse(MessageBase::Type type, qint32 x, qint32 y)
    : MessageBase(type, "")
{
    _messageString = QString::number((qint32) type);
    _messageString += " ";
    _messageString = QString::number(x);
    _messageString += " ";
    _messageString = QString::number(y);
}

MessageMouse::~MessageMouse()
{
}

const QPoint &MessageMouse::point() const
{
    return _point;
}

qint32 MessageMouse::x() const
{
    return _point.x();
}

qint32 MessageMouse::y() const
{
    return _point.y();
}

