#include "PlayerInfos.hh"

PlayerInfos::PlayerInfos(quint32 number, const QPoint &position)
    : _number(number),
      _position(position),
      _score(0),
      _lives(0),
      _pseudo(""),
      _scoreText(""),
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
    _scoreText = QString::number(_score);
}

quint32 PlayerInfos::score() const
{
    return _score;
}

void PlayerInfos::lives(quint32 lives)
{
    _lives = lives;
}

quint32 PlayerInfos::lives() const
{
    return _lives;
}

quint32 PlayerInfos::number() const
{
    return _number;
}

const QString &PlayerInfos::pseudo() const
{
    return _pseudo;
}

void PlayerInfos::pseudo(const QString &pseudo)
{
    _pseudo = pseudo;
}

void PlayerInfos::draw(QPainter &painter, Images &images) const
{
    painter.setPen(_color);
    painter.setBrush(_brush);
    painter.drawText(_position, _pseudo);
    painter.drawText(_position.x(), _position.y() + 15, _scoreText);

    /* Draw lives */
    for (quint32 i = 0; i < _lives; ++i)
    {
        painter.drawImage (_position.x() + i * 24, _position.y() + 25, images.getImage(Element::LIVE));
    }
}
