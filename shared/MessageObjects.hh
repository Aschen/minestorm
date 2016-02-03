#ifndef MESSAGEOBJECTS_HH
# define MESSAGEOBJECTS_HH

# include <QTextStream>
# include <QSharedPointer>
# include <QVector>
# include <QPolygon>

# include <cassert>

# include "MessageBase.hh"
# include "Entity.hh"
# include "Ship.hh"

class MessageObjects : public MessageBase
{
private:
    QSharedPointer<QVector<QPolygon>>           _objects;

public:
    MessageObjects(const QString &msg);
    MessageObjects(const QVector<QPolygon> &objects);
    MessageObjects(const EntityHash &entities);
    ~MessageObjects();

    const QSharedPointer<QVector<QPolygon>>     &objects() const;

private:
    void                serializeShip(const Ship &ship);
};

/*
 * Frame :
 *  |messageType objectsCount imgId pointsCount x y imgId pointCount x y |
 */

/*
 * Ship
 *  - imgId
 *  - 3 QPoint
 * |"1 3 x1 y1 x2 y2 x3 y3"|
 */

#endif // MESSAGEOBJECTS_HH
