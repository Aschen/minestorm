#include "Core.hh"

Core::Core(const QSize &size, QObject *parent)
    : Game(size, parent)
{
    shared_ptr<DrawableObject>      rec = shared_ptr<DrawableObject>(new DrawableObject());

    *rec << QPoint(5, 5) << QPoint(80, 5) << QPoint(80, 80) << QPoint(5, 60);
    _objects.push_front(rec);
}



void Core::draw(QPainter &painter, QRect &size)
{
    painter.setPen(QColor(236, 248, 230));
    painter.setBrush(QBrush(QColor(236, 248, 230)));

    for (auto object : _objects)
    {
        painter.drawConvexPolygon(*object);
    }
}

void Core::mousePressed(int x, int y)
{
}

void Core::mouseReleased(int x, int y)
{
}

void Core::mouseMoved(int x, int y)
{
}

void Core::keyPressed(int key)
{
}

void Core::keyReleased(int key)
{
}

void Core::step()
{
}

void Core::initialize()
{
}
