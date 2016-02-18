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

# define BUF_SIZE 15

class MessageObjects : public MessageBase
{
private:
    QSharedPointer<QVector<Element>>           _elements;
    char                                       _buf[BUF_SIZE];

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
    char                *write_nbr(qint32 nbr);
    quint32             nbr_length(qint32 nbr);
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
