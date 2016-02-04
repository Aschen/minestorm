#include "MessageObjects.hh"

MessageObjects::MessageObjects(const QString &msg)
    : MessageBase(MessageBase::INFO_OBJECTS, msg)
{
    QTextStream         stream(msg.toUtf8());
    qint32              type;
    quint32             objectsCount;
    quint32             pointsCount;
    qint32              x;
    qint32              y;

    stream >> type;
    assert(type == (qint32) MessageBase::INFO_OBJECTS);

    /* Stream: "7 total count x1 y1 x2 y2 count x1 y1 x2 y2 x3 y3"  Ex: "7 3 2 x y x y 3 x y x y x y 1 x y" */
    // Initialize vector size with objects count
    stream >> objectsCount;
    _objects = QSharedPointer<QVector<QPolygon>>(new QVector<QPolygon>(objectsCount));

    for (quint32 i = 0; i < objectsCount; ++i)
    {
        // Initialize a polygon with pointsCount points
        stream >> pointsCount;
        QPolygon    object(pointsCount);

        for (quint32 j = 0; j < pointsCount; ++j)
        {
            // For each pair of coordinate, add point to the polygon
            stream >> x >> y;
            object[j] = QPoint(x, y);
        }
        _objects->operator[](i) = object;
    }
}

MessageObjects::MessageObjects(const EntityHash &entities)
    : MessageBase(MessageBase::INFO_OBJECTS, ""),
      _objects(nullptr)
{
    /* Write message type */
    _messageString = QString::number((qint32) _type) + " ";

    /* Write total objects count */
    _messageString += QString::number(entities.count()) + " ";

    /* Write each object */
    for (const QSharedPointer<Entity> &entity : entities)
    {
        /* Write object type */
        _messageString += QString::number((qint32) entity->type()) + " ";

        switch (entity->type())
        {
        case Entity::SHIP:
            serializeShip(dynamic_cast<Ship&>(*entity));
            break;

        default:
            DEBUG("MessageObjects::MessageObjects() : Unknown entity" << entity->type(), true);
            assert(false);
            break;
        }
    }
}

MessageObjects::~MessageObjects()
{
}

const QSharedPointer<QVector<QPolygon>> &MessageObjects::objects() const
{
    return _objects;
}

void MessageObjects::serializeShip(const Ship &ship)
{
    /* Write id ship */
    _messageString += QString::number(ship.id()) + " ";

    /* Write points count */
    _messageString += QString::number(ship.count()) + " ";

    /* Write coordinates for each point */
    for (const QPoint &point : ship)
    {
        _messageString += QString::number(point.x()) + " ";
        _messageString += QString::number(point.y()) + " ";
    }

}

