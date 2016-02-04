#include "MessageObjects.hh"

/* DESERIALIZE ***************************************************************/
MessageObjects::MessageObjects(const QString &msg)
    : MessageBase(MessageBase::INFO_OBJECTS, msg),
      _elements(new QVector<Element>(0))
{
    QTextStream         stream(msg.toUtf8());
    qint32              messageType;
    quint32             objectsCount;
    qint32              objectType;

    /* Read  message type*/
    stream >> messageType;
    assert(messageType == (qint32) MessageBase::INFO_OBJECTS);

    /* Read objects count */
    stream >> objectsCount;

    for (quint32 i = 0; i < objectsCount; ++i)
    {
        /* Read object type */
        stream >> objectType;

        switch (objectType)
        {
        case Entity::SHIP:
            deserializeShip(stream);
            break;
        case Entity::MINE:
            break;
        default:
            DEBUG("MessageObjects::MessageObjects() : Unknown entity" << messageType, true);
            break;
        }
    }
}

/* shipNumber x1 y1 x2 y2 x3 y3 */
void MessageObjects::deserializeShip(QTextStream &stream)
{
    quint32     shipNumber;
    QPolygon    polygon(3);
    qint32      x;
    qint32      y;

    /* Read shipNumber */
    stream >> shipNumber;

    /* Read 3 points */
    for (quint32 i = 0; i < 3; ++i)
    {
        // For each pair of coordinate, add point to the polygon
        stream >> x >> y;
        polygon[i] = QPoint(x, y);
    }

    _elements->push_back(Element((Element::Type) shipNumber, polygon));
}

/* SERIALIZE *******************************************************************/
MessageObjects::MessageObjects(const EntityHash &entities)
    : MessageBase(MessageBase::INFO_OBJECTS, ""),
      _elements(nullptr)
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

        case Entity::CARRE:
            serializeCarre(dynamic_cast<Carre&>(*entity));
            break;

        case Entity::MINE:

            break;

        default:
            DEBUG("MessageObjects::MessageObjects() : Unknown entity" << entity->type(), true);
            assert(false);
            break;
        }
    }
}

/* shipNumber x1 y1 x2 y2 x3 y3 */
void MessageObjects::serializeShip(const Ship &ship)
{
    _messageString += QString::number(ship.shipNumber()) + " ";

    for (const QPoint &point : ship)
    {
        _messageString += QString::number(point.x()) + " ";
        _messageString += QString::number(point.y()) + " ";
    }
}

void MessageObjects::serializeCarre(const Carre &carre)
{
    /* Write color carre */
    _messageString += QString::number(carre.color()) + " ";

    /* Write points count */
    _messageString += QString::number(carre.count()) + " ";

    /* Write coordinates for each point */
    for (const QPoint &point : carre)
    {
        _messageString += QString::number(point.x()) + " ";
        _messageString += QString::number(point.y()) + " ";
    }
}

MessageObjects::~MessageObjects()
{
}

const QSharedPointer<QVector<Element>> &MessageObjects::elements() const
{
    return _elements;
}
