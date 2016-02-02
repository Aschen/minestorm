#ifndef MESSAGE_HH
# define MESSAGE_HH

# include <QString>
# include <QHash>

class MessageBase
{
public:
    enum Type
    {
        ERROR = 0, // Trying to extract int from QTextStream return 0 if error
        MOUSE_PRESSED = 1,
        MOUSE_RELEASED = 2,
        KEY_PRESSED = 3,
        KEY_RELEASED = 4,
        INFO_START = 5,
        INFO_STOP = 6,
        INFO_OBJECTS = 7
    };
    static const QHash<Type, QString>   STRINGS;

protected:
    Type                                _type;
    QString                             _messageString;


public:
    MessageBase(Type type, const QString &messageString);
    virtual ~MessageBase();

    QString                             typeStr() const;
    MessageBase::Type                   type() const;
    const QString                       &messageString() const;
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
  * INFO_OBJECTS :  |frameSize|"7 total count p1 p2 count p1 p2 p3"|  (|7 3 2 x y 3 x y z 1 x|)
  */

#endif // MESSAGE_HH
