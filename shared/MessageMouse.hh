#ifndef MESSAGEMOUSE_HH
# define MESSAGEMOUSE_HH

# include <QPoint>
# include <QTextStream>

# include <cassert>

# include "MessageBase.hh"

class MessageMouse : public MessageBase
{
private:
    QPoint          _point;

public:
    MessageMouse(const QString &msg);
    MessageMouse(MessageBase::Type type, QTextStream &stream);
    MessageMouse(MessageBase::Type type, qint32 x, qint32 y);
    ~MessageMouse();

    const QPoint        &point() const;
    qint32              x() const;
    qint32              y() const;

private:
    void                createPoint(QTextStream &stream);
};

#endif // MESSAGEMOUSE_HH
