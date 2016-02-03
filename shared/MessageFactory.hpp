#ifndef MESSAGEFACTORY_HPP
# define MESSAGEFACTORY_HPP

# include <QTextStream>

# include "Minestorm.hh"
# include "MessageBase.hh"
# include "MessageMouse.hh"
# include "MessageKey.hh"
# include "MessageObjects.hh"

class MessageFactory
{
public:
    static MessageBase      *make(const QString &msg)
    {
        MessageBase         *message = nullptr;
        QTextStream         stream(msg.toUtf8());
        qint32              type;
        MessageBase::Type   msgType;

        stream >> type;
        msgType = (MessageBase::Type) type;

        switch (msgType)
        {
        case MessageBase::MOUSE_PRESSED:
        case MessageBase::MOUSE_RELEASED:
            message = new MessageMouse(msgType, stream);
            break;

        default:
            DEBUG("MessageFactory::make() : Unknown message type" << type, true);
            break;
        }

        return message;
    }
};

#endif // MESSAGEFACTORY_HPP

