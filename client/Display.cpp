#include "Display.hh"

Display::Display(const QSize &size, int fps, QObject *parent)
    : QObject(parent),
      _isRunning(false),
      _size(size),
      _fps(fps),
      _client("127.0.0.1", 4242),
      _objects(nullptr)
{
    qDebug() << "Display::Display()";
    _timer.setSingleShot(false);
    /* Le signal timeout() est envoyé toutes les 40ms,
    ** on le connecte à la fonction Display::update()
    ** qui fait appel à GameBoard::paintEvent()
    ** qui fait appel à Display::draw()
    */
    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));

    /* Quand le client reçoit la liste des objets,
    ** on appelle la fonction d'affichage
    */
    connect(&_client,   SIGNAL(receiveInfoObjects(QSharedPointer<QVector<QPolygon>>)),
            this,       SLOT(receiveObjects(QSharedPointer<QVector<QPolygon>>)));
}

/* *** */
void Display::draw(QPainter &painter, QRect &size)
{
    (void) size;
    DEBUG("Display::draw() : " << _objects->size() << " objects to draw", 0);
    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(QBrush(QColor(0, 0, 0)));

    if (_objects != nullptr)
    {
        _objectsMutex.lock();
        for (auto object : *_objects)
        {
            painter.drawConvexPolygon(object);
        }
        _objectsMutex.unlock();
    }
}

void Display::initialize()
{
}

void Display::start()
{
    DEBUG("Display::start()", 0);
    _timer.start(1000 / _fps); // Répète le timer en fonction des fps
    _isRunning = true;
    _client.start();
    emit sigStart();
}

void Display::pause()
{
    DEBUG("Display::pause()", 0);
    _timer.stop();
    _isRunning = false;
    emit sigPause();
}

void Display::reset()
{
    DEBUG("Display::reset()", 0);
    pause();
    initialize();
    emit changed();
    emit sigReset();
}

void Display::test()
{
    DEBUG("Display::test()", 1);

    emit sigTest();
}

void Display::update()
{
    DEBUG("Display::update()", 0);
    if (_isRunning)
    {
        emit changed();
    }
}


/* EVENTS */
void Display::mousePressed(int x, int y)
{
    qDebug() << "Display::mousePressed : x = " << x << ", y = " << y;
    _client.sendMessage("1 " + QString::number(x) + " " + QString::number(y));
    emit sigMousePressed(x, y);
}

void Display::mouseReleased(int x, int y)
{
    emit sigMouseReleased(x, y);
}

void Display::mouseMoved(int x, int y)
{
    emit sigMouseMoved(x, y);
}

void Display::keyPressed(int key)
{
    emit sigKeyPressed(key);
}

void Display::keyReleased(int key)
{
    emit sigKeyReleased(key);
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

const QVector<QPolygon> &Display::objects() const
{
    return *_objects;
}

void Display::receiveObjects(const QSharedPointer<QVector<QPolygon>> &objects)
{
    DEBUG("Display::receiveObjects() : " << objects->size() << " objects received", 1);
    _objectsMutex.lock();
    _objects = objects;
    _objectsMutex.unlock();
}
