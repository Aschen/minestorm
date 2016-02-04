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
# include "Carre.hh"
# include "Element.hh"

class MessageObjects : public MessageBase
{
private:
    QSharedPointer<QVector<Element>>           _elements;

public:
    MessageObjects(const QString &msg);
    MessageObjects(const EntityHash &entities);
    ~MessageObjects();

    const QSharedPointer<QVector<Element>>     &elements() const;

private:
    void                deserializeShip(QTextStream &stream);
    void                serializeShip(const Ship &ship);
    void                serializeCarre(const Carre &carre);

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
