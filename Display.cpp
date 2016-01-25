#include "Display.hh"

Display::Display(const QSize &size, QObject *parent)
    : QObject(parent),
      _isRunning(false),
      _size(size)
{
    _timer.setSingleShot(false);
    /* Le signal timeout() est envoyé toutes les 40ms,
    ** on le connecte à la fonction Display::update()
    */
    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
}

/* *** */
void Display::draw(QPainter &painter, QRect &size)
{
//    painter.setPen(QColor(236, 248, 230));
//    painter.setBrush(QBrush(QColor(236, 248, 230)));

//    for (auto object : _objects)
//    {
//        painter.drawConvexPolygon(*object);
//    }
}

void Display::initialize()
{
}

void Display::start()
{
    _timer.start(40); // Répète le timer toutes les 40ms (25 fps)
    _isRunning = true;
    DEBUG("start()");
}

void Display::pause()
{
    _timer.stop();
    _isRunning = false;
    DEBUG("pause()");
}

void Display::reset()
{
    pause();
    initialize();
    emit changed();
    DEBUG("reset()");
}

void Display::update()
{
    if (_isRunning)
    {
        emit changed();
        DEBUG("update()");
    }
}


/* EVENTS */
void Display::mousePressed(int x, int y)
{
    DEBUG("mousePressed(" << x << ", " << y << ")");
}

void Display::mouseReleased(int x, int y)
{
    DEBUG("mouseReleased(" << x << ", " << y << ")");
}

void Display::mouseMoved(int x, int y)
{
    DEBUG("mouseMoved(" << x << ", " << y << ")");
}

void Display::keyPressed(int key)
{
    DEBUG("keyPressed(" << key << ")");
}

void Display::keyReleased(int key)
{
    DEBUG("keyReleased(" << key << ")");
}

/* GETTERS/SETTERS */

const QSize &Display::size() const
{
    return _size;
}

bool Display::isRunning() const
{
    return _isRunning;
}
