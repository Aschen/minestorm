#ifndef PROTOCOL_HH
# define PROTOCOL_HH

# include <QString>
# include <QPoint>
# include <QHash>
# include <QTextStream>

class Protocol
{
public:
    enum MessageType
    {
        MOUSE_PRESSED = 1,
        MOUSE_RELEASED
    };

    static const QHash<MessageType, QString>    MESSAGES;

    static Protocol::MessageType   getMessage(const QString &msg);

    /*
     * trame : "MOUSE_PRESSED x y"
     */
    static QString                  mousePressed(int x, int y);
    static QPoint                   mousePressed(const QString &msg);




private:
    Protocol() {}
};

#endif // PROTOCOL_HH
