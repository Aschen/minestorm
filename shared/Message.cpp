#include "Message.hh"

Message::Message(const QString &msg)
    : _rawMessage(msg),
      _type(ERROR),
      _keyCode(-1),
      _point(nullptr),
      _objects(nullptr)
{
    qDebug() << "Message::Message() : " <<_rawMessage;
    QTextStream     stream(msg.toUtf8());
    int             type;

    stream >> type;
    _type = (Message::Type) type;

    switch (_type)
    {
    case MOUSE_PRESSED:
    case MOUSE_RELEASED:
        readMouseEvent (stream);
        break;

    case KEY_PRESSED:
    case KEY_RELEASED:
        readKeyEvent(stream);
        break;

    case INFO_START:
    case INFO_STOP:
        break;

    case INFO_OBJECTS:
        readInfoObjects(stream);
        break;

    case ERROR:
    default:
        qDebug() << "Unknown message type " << _type;
        _type = Message::ERROR;
        break;
    }
}

Message::~Message()
{
}

Message::Type Message::type() const
{
    return _type;
}

int Message::keyCode() const
{
    return _keyCode;
}

QString Message::typeStr() const
{
    return Message::STRINGS[_type];
}

const QSharedPointer<QPoint> Message::point() const
{
    return _point;
}

const QSharedPointer<QVector<QPolygon>> Message::objects() const
{
    return _objects;
}

void Message::readMouseEvent(QTextStream &stream)
{
    qint32      x;
    qint32      y;

    stream >> x >> y;

    _point = QSharedPointer<QPoint>(new QPoint(x, y));
}

void Message::readKeyEvent(QTextStream &stream)
{
   stream >> _keyCode;
}

void Message::readInfoObjects(QTextStream &stream)
{
    /* Stream: "7 total count x1 y1 x2 y2 count x1 y1 x2 y2 x3 y3"  Ex: "7 3 2 x y x y 3 x y x y x y 1 x y" */
    quint32     objectsCount;
    quint32     pointsCount;
    qint32      x;
    qint32      y;

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

const QHash<Message::Type, QString> Message::STRINGS = {
    { Message::ERROR, "ERROR" },
    { Message::MOUSE_PRESSED, "MOUSE_PRESSED" },
    { Message::MOUSE_RELEASED, "MOUSE_RELEASED" },
    { Message::KEY_PRESSED, "KEY_PRESSED" },
    { Message::KEY_RELEASED, "KEY_RELEASED" },
    { Message::INFO_START, "INFO_START" },
    { Message::INFO_STOP, "INFO_STOP" },
    { Message::INFO_OBJECTS, "INFO_OBJECTS" }
};

QDebug &operator<<(QDebug &qdebug, Message::Type msgType)
{
    qdebug << Message::STRINGS[msgType];

    return qdebug;
}

QDebug &operator<<(QDebug &qdebug, const Message &msg)
{
    qdebug << msg.typeStr();

    switch (msg.type())
    {
    case Message::MOUSE_PRESSED:
    case Message::MOUSE_RELEASED:
        qdebug << "x: " << msg.point()->x() << " y: " << msg.point()->y();
        break;

    case Message::KEY_PRESSED:
    case Message::KEY_RELEASED:
        qdebug << "keyCode: " << msg.keyCode();
        break;

    case Message::INFO_START:
    case Message::INFO_STOP:
        break;

    case Message::INFO_OBJECTS:
        qdebug << "count: " << msg.objects()->size();
        break;

    case Message::ERROR:
        break;
    }

    return qdebug;
}
