#ifndef MESSAGE_HH
# define MESSAGE_HH

# include <QString>
# include <QHash>

# include "Minestorm.hh"

class MessageBase
{
public:
    enum Type
    {
        ERROR = 0, // Trying to extract int from QTextStream return 0 if error
        MOUSE_PRESSED,
        KEY_PRESSED,
        KEY_RELEASE,
        OBJECTS,
        PLAYERS_INFOS,
        PSEUDO
    };

protected:
    Type                                _type;
    QString                             _messageString;

public:
    MessageBase(Type type, const QString &messageString);
    virtual ~MessageBase();

    MessageBase::Type                   type() const;
    const QString                       &messageString() const;

    static  MessageBase::Type           getMessageType(const QString &msg);
};

/**
  *           quint16               frameSize
  * Frame : |frameSize|"messageType message...................."|
  *
  * M_PRESSED :     |frameSize|"1 x y"|
  * M_RELEASED :    |frameSize|"2 x y"|
  * K_PRESSED :     |frameSize|"3 key"|
  * K_RELEASED :    |frameSize|"4 key"|
  * INFO_START :    |frameSize|"5"|
  * INFO_STOP :     |frameSize|"6"|
  * OBJECTS :  |frameSize|"7 total count p1 p2 count p1 p2 p3"|  (|7 3 2 x y 3 x y z 1 x|)
  */

#endif // MESSAGE_HH
