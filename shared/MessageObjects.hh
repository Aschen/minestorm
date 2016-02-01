#ifndef MESSAGEOBJECTS_HH
# define MESSAGEOBJECTS_HH

# include <QTextStream>
# include <QSharedPointer>
# include <QVector>
# include <QPolygon>

# include <cassert>

# include "MessageBase.hh"

class MessageObjects : public MessageBase
{
private:
    QSharedPointer<QVector<QPolygon>>           _objects;

public:
    MessageObjects(const QString &msg);
    MessageObjects(const QVector<QPolygon> &objects);
    ~MessageObjects();

    const QSharedPointer<QVector<QPolygon>>     &objects() const;
};

#endif // MESSAGEOBJECTS_HH
