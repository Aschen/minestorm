#include "FpsCounter.hh"

FpsCounter::FpsCounter()
    : _frameCount(0),
      _text(""),
      _color(QColor(255, 255, 255)),
      _brush(QBrush(_color)),
      _position(QPoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30))
{
    _timer.setSingleShot(false);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(count()));
    connect(this, SIGNAL(stopTimer()), &_timer, SLOT(stop()));
}

void FpsCounter::start()
{
    _timer.start(1000);
}

void FpsCounter::stop()
{
    _frameCount = 0;
    emit stopTimer();
}

void FpsCounter::frameDraw()
{
    _frameCount++;
}

const QString &FpsCounter::fpsText() const
{
    return _text;
}

void FpsCounter::draw(QPainter &painter, Images &images) const
{
    (void) images;
    painter.setPen(_color);
    painter.setBrush(_brush);
    painter.drawText(_position, _text);
}

void FpsCounter::count()
{
    _text = QString::number(_frameCount);
    _frameCount = 0;
}
