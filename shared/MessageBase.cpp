#include "MessageBase.hh"

MessageBase::MessageBase(Type type, const QString &messageString)
    : _type(type),
      _messageString(messageString)
{
}

MessageBase::~MessageBase()
{
}

MessageBase::Type MessageBase::type() const
{
    return _type;
}

const QString &MessageBase::messageString() const
{
    return _messageString;
}

QString MessageBase::typeStr() const
{
    return MessageBase::STRINGS[_type];
}

//int MessageBase::keyCode() const
//{
//    return _keyCode;
//}

//const QSharedPointer<QPoint> MessageBase::point() const
//{
//    return _point;
//}

//const QSharedPointer<QVector<QPolygon>> MessageBase::objects() const
//{
//    return _objects;
//}

//void MessageBase::readMouseEvent(QTextStream &stream)
//{
//    qint32      x;
//    qint32      y;

//    stream >> x >> y;

//    _point = QSharedPointer<QPoint>(new QPoint(x, y));
//}

//void MessageBase::readKeyEvent(QTextStream &stream)
//{
//   stream >> _keyCode;
//}

//void MessageBase::readInfoObjects(QTextStream &stream)
//{
//    /* Stream: "7 total count x1 y1 x2 y2 count x1 y1 x2 y2 x3 y3"  Ex: "7 3 2 x y x y 3 x y x y x y 1 x y" */
//    quint32     objectsCount;
//    quint32     pointsCount;
//    qint32      x;
//    qint32      y;

//    // Initialize vector size with objects count
//    stream >> objectsCount;
//    _objects = QSharedPointer<QVector<QPolygon>>(new QVector<QPolygon>(objectsCount));

//    for (quint32 i = 0; i < objectsCount; ++i)
//    {
//        // Initialize a polygon with pointsCount points
//        stream >> pointsCount;
//        QPolygon    object(pointsCount);

//        for (quint32 j = 0; j < pointsCount; ++j)
//        {
//            // For each pair of coordinate, add point to the polygon
//            stream >> x >> y;
//            object[j] = QPoint(x, y);
//        }
//        _objects->operator[](i) = object;
//    }
//}

const QHash<MessageBase::Type, QString> MessageBase::STRINGS = {
    { MessageBase::ERROR, "ERROR" },
    { MessageBase::MOUSE_PRESSED, "MOUSE_PRESSED" },
    { MessageBase::MOUSE_RELEASED, "MOUSE_RELEASED" },
    { MessageBase::KEY_PRESSED, "KEY_PRESSED" },
    { MessageBase::KEY_RELEASED, "KEY_RELEASED" },
    { MessageBase::INFO_START, "INFO_START" },
    { MessageBase::INFO_STOP, "INFO_STOP" },
    { MessageBase::INFO_OBJECTS, "INFO_OBJECTS" }
};
