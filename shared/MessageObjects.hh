#ifndef MESSAGEOBJECTS_HH
# define MESSAGEOBJECTS_HH

# include <QTextStream>
# include <QSharedPointer>
# include <QVector>
# include <QPolygon>

# include <cassert>
# include <cstdlib>
# include <stdlib.h>
# include <cstdio>
# include <stdio.h>

# include "MessageBase.hh"
# include "Entity.hh"
# include "Ship.hh"
# include "Mine.hh"
# include "Projectile.hh"
# include "Element.hh"

class MessageObjects : public MessageBase
{
private:
    QSharedPointer<QVector<Element>>           _elements;
//    char buf[sizeof(qint32)*8+1];

public:
    MessageObjects(const QString &msg);
    MessageObjects(const EntityList &entities);
    ~MessageObjects();

    const QSharedPointer<QVector<Element>>     &elements() const;

private:
    void                deserializeShip(QTextStream &stream);
    void                deserializeShot(QTextStream &stream);
    void                deserializeMine(QTextStream &stream);
    void                serializeShip(const Ship &ship);
    void                serializeShot(const Projectile &shot);
    void                serializeMine(const Mine &mine);
//    void                put_nbr(char *buf, quint32 i);
};

/*
 * Frame :
 *  | messageType | elementsCount | elementsType | data |
 */

/*
 * Ship
 *  - imgId
 *  - 3 QPoint
 * |"1 3 x1 y1 x2 y2 x3 y3"|
 */

#endif // MESSAGEOBJECTS_HH
