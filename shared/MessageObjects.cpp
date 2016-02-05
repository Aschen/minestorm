#include "MessageObjects.hh"

/* DESERIALIZE ***************************************************************/
MessageObjects::MessageObjects(const QString &msg)
    : MessageBase(MessageBase::OBJECTS, msg),
      _elements(new QVector<Element>(0))
{
    QTextStream         stream(msg.toUtf8());
    qint32              messageType;
    quint32             objectsCount;
    qint32              objectType;

    /* Read  message type*/
    stream >> messageType;
    assert(messageType == (qint32) MessageBase::OBJECTS);
    DEBUG("MessageObjects::MessageObjects() : Message:" << msg, false);

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
        case Entity::SHOT:
            deserializeShot(stream);
            break;
        case Entity::MINE:
            break;
        default:
            DEBUG("MessageObjects::MessageObjects() : Unknown entity" << messageType, true);
            break;
        }
    }
}

/* shipNumber angle center_x center_y x1 y1 x2 y2 x3 y3*/
void MessageObjects::deserializeShip(QTextStream &stream)
{
    quint32     shipNumber;
    QPolygon    polygon(3);
    qreal       angle;
    qint32      center_x;
    qint32      center_y;
    qint32      x;
    qint32      y;

    /* Read shipNumber angle center_x center_y */
    stream >> shipNumber >> angle >> center_x >> center_y;

    /* Read 3 points */
    for (quint32 i = 0; i < 3; ++i)
    {
        stream >> x >> y;
        polygon[i] = QPoint(x, y);
    }
    DEBUG("MessageObjects::deserializeShip() : Ship n°" << shipNumber << " angle: " << angle << " center:" << x << y
          , false);
    _elements->push_back(Element((Element::Type) shipNumber, polygon, angle, QPoint(center_x, center_y)));
}

/* x1 y1 x2 y2 */
void MessageObjects::deserializeShot(QTextStream &stream)
{
    QPolygon    polygon(2);
    qint32      x;
    qint32      y;

    /* Read 2 points */
    for (quint32 i = 0; i < 2; ++i)
    {
        stream >> x >> y;
        polygon[i] = QPoint(x, y);
    }
    DEBUG("MessageObjects::deserializeShot()", false);
    _elements->push_back(Element(Element::SHOT, polygon));
}

/* SERIALIZE *******************************************************************/
MessageObjects::MessageObjects(const EntityHash &entities)
    : MessageBase(MessageBase::OBJECTS, ""),
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
        case Entity::SHOT:
            serializeShot(dynamic_cast<Projectile&>(*entity));
            break;
        case Entity::MINE:
            break;
        case Entity::SHOT:
            break;
        default:
            DEBUG("MessageObjects::MessageObjects() : Unknown entity" << entity->type(), true);
            assert(false);
            break;
        }
    }
}

/* shipNumber angle center_x center_y x1 y1 x2 y2 x3 y3*/
void MessageObjects::serializeShip(const Ship &ship)
{
    /* Write shipNumber */
    _messageString += QString::number(ship.shipNumber()) + " ";

    /* Write angle */
    _messageString += QString::number(ship.angle()) + " ";

    /* Write center */
    _messageString += QString::number(ship.center().x()) + " ";
    _messageString += QString::number(ship.center().y()) + " ";

    /* Write 3 points */
    for (quint32 i = 0; i < 3; ++i)
    {
        _messageString += QString::number(ship[i].x()) + " ";
        _messageString += QString::number(ship[i].y()) + " ";
    }
}

/* x1 y1 x2 y2 */
void MessageObjects::serializeShot(const Projectile &shot)
{
    /* Write 2 points */
    for (quint32 i = 0; i < 2; ++i)
    {
        _messageString += QString::number(shot[i].x()) + " ";
        _messageString += QString::number(shot[i].y()) + " ";
    }
}

MessageObjects::~MessageObjects()
{
}

const QSharedPointer<QVector<Element>> &MessageObjects::elements() const
{
    return _elements;
}
