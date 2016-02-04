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
    DEBUG("MessageObjects::MessageObjects() : Message:" << msg, true);

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

/* shipNumber angle center_x center_y */
void MessageObjects::deserializeShip(QTextStream &stream)
{
    quint32     shipNumber;
    QPolygon    polygon(1);
    qreal       angle;
    qint32      x;
    qint32      y;

    /* Read shipNumber angle center_x center_y */
    stream >> shipNumber >> angle >> x >> y;

    polygon[0] = QPoint(x, y);

    DEBUG("MessageObjects::deserializeShip() : Ship n°" << shipNumber << " angle: " << angle << " center:" << x << y
          , true);
    _elements->push_back(Element((Element::Type) shipNumber, polygon, angle));
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
        case Entity::MINE:
            break;
        default:
            DEBUG("MessageObjects::MessageObjects() : Unknown entity" << entity->type(), true);
            assert(false);
            break;
        }
    }
}

/* shipNumber angle center_x center_y */
void MessageObjects::serializeShip(const Ship &ship)
{
    /* Write shipNumber */
    _messageString += QString::number(ship.shipNumber()) + " ";

    /* Write angle */
    _messageString += QString::number(ship.angle()) + " ";

    /* Write center */
    _messageString += QString::number(ship.center().x()) + " ";
    _messageString += QString::number(ship.center().y()) + " ";
}

MessageObjects::~MessageObjects()
{
}

const QSharedPointer<QVector<Element>> &MessageObjects::elements() const
{
    return _elements;
}
