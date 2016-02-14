#include "PlayerInfos.hh"

PlayerInfos::PlayerInfos(quint32 number, const QPoint &position)
    : _number(number),
      _position(position),
      _score(0),
      _lives(0),
      _scoreText(""),
      _livesText(""),
      _color(QColor(255, 255, 255)),
      _brush(QBrush(_color))
{
}

PlayerInfos::~PlayerInfos()
{
}

void PlayerInfos::score(quint32 score)
{
    _score = score;
    _scoreText = QString("Score: ") + QString::number(_score);
}

quint32 PlayerInfos::score() const
{
    return _score;
}

void PlayerInfos::lives(quint32 lives)
{
    _lives = lives;
    _livesText = QString("Vies: ") + QString::number(_lives);
}

quint32 PlayerInfos::lives() const
{
    return _lives;
}

quint32 PlayerInfos::number() const
{
    return _number;
}

void PlayerInfos::draw(QPainter &painter, Images &images) const
{
    (void) images;
    painter.setPen(_color);
    painter.setBrush(_brush);
    painter.drawText(_position, "Player " + QString::number(_number));
    painter.drawText(_position.x(), _position.y() + 15, _livesText);
    painter.drawText(_position.x(), _position.y() + 30, _scoreText);
}
