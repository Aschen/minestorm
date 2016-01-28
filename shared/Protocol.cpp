#include "Protocol.hh"

QString Protocol::mousePressed(int x, int y)
{
    // Need std::stringstream equivalent !!
    QString     message;

    message += Protocol::MESSAGES[Protocol::MOUSE_PRESSED];
    message += " ";
    message += QString::number(x);
    message += " ";
    message += QString::number(y);

    return message;
}

QPoint Protocol::mousePressed(const QString &msg)
{
    QTextStream     stream(msg.toUtf8());
    qint32          x;
    qint32          y;

    stream >> x >> y;

    return QPoint(x, y);
}

const QHash<Protocol::MessageType, QString> Protocol::MESSAGES = {
  { Protocol::MOUSE_PRESSED, "MOUSE_PRESSED" },
  { Protocol::MOUSE_RELEASED, "MOUSE_RELEASED" }
};
