#include "GameBoard.hh"

GameBoard::GameBoard(Display *display, QWidget *parent)
    : QWidget(parent),
      _display(display),
      _acceptEvent(true)
{
    connect(_display, SIGNAL(changed()), this, SLOT(update()));

    setMinimumSize(_display->size());
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    setObjectName("GameBoard");

    /*
     * On utilise un timer pour limiter le nombre d'events
     */
//    _timer.setSingleShot(true);
//    connect(&_timer, SIGNAL(timeout()), this, SLOT(acceptEvent()));
    //        _acceptEvent = false;
    //        _timer.start(1000 / EVENT_PER_S);
}

void GameBoard::paintEvent(QPaintEvent * /* event */ )
{
    QPainter painter;
    painter.begin(this);
    auto rectT = rect();
    _display->draw(painter, rectT);
    painter.end();
}

void GameBoard::mousePressEvent (QMouseEvent * event)
{
    event->accept();
    // normalise les coordonnées pour le remettre à la taille du jeu
    auto x = event->x() * _display->size().width() / (double) rect().width();
    auto y = event->y() * _display->size().height() / (double) rect().height();
    _display->mousePressed(x, y);
}

void GameBoard::keyPressEvent(QKeyEvent * event)
{
    if (!event->isAutoRepeat())
    {
        _display->keyPressed(event->key());
    }
}

void GameBoard::keyReleaseEvent(QKeyEvent * event)
{
    if (!event->isAutoRepeat())
    {
        _display->keyReleased(event->key());
    }
}

void GameBoard::acceptEvent()
{
    DEBUG("GameBoard::acceptEvent()", false);

    _acceptEvent = true;
}
