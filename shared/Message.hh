#ifndef MESSAGE_HH
# define MESSAGE_HH

# include <QTextStream>
# include <QHash>
# include <QDebug>
# include <QPoint>
# include <QSharedPointer>
# include <QVector>
# include <QPolygon>

class Message
{
public:
    enum Type
    {
        ERROR = 0, // Error when try to extract int from QTextStream return 0
        MOUSE_PRESSED = 1,
        MOUSE_RELEASED = 2,
        KEY_PRESSED = 3,
        KEY_RELEASED = 4,
        INFO_START = 5,
        INFO_STOP = 6,
        INFO_OBJECTS = 7
    };
    static const QHash<Type, QString>   STRINGS;

private:
    const QString                       _rawMessage;
    Type                                _type;
    int                                 _keyCode;
    QSharedPointer<QPoint>              _point; // Make union?
    QSharedPointer<QVector<QPolygon>>   _objects;


public:
    Message(const QString &msg);
    ~Message();

    Message::Type                       type() const;
    int                                 keyCode() const;
    QString                             typeStr() const;
    const QSharedPointer<QPoint>        point() const;
    const QSharedPointer<QVector<QPolygon>> objects() const;

private:
    void                                readMouseEvent(QTextStream &stream);
    void                                readKeyEvent(QTextStream &stream);
    void                                readInfoObjects(QTextStream &stream);
};


QDebug              &operator<<(QDebug &qdebug, const Message &msg);
QDebug              &operator<<(QDebug &qdebug, Message::Type msgType);

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
