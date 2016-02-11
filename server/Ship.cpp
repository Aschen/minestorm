#include "Ship.hh"


Ship::Ship(qint32 id, const QPointF &position, qint32 shipNumber)
    : Entity(id, Entity::SHIP),
      _vie(3),
      _shipNumber(shipNumber),
      _tempo(0),
      _score(0),
      _scoreChanged(false)
{
    _size   = QSize(SHIP_SIZE, SHIP_SIZE);
    _speed  = 0;
    _angle  = 0;
    this->addPoint(QPointF(position.x(), position.y()));
    this->addPoint(QPointF(position.x() + size().width(), position.y()));
    this->addPoint(QPointF(position.x() + size().height(), position.y() + size().width()));
    this->addPoint(QPointF(position.x(), position.y() + size().height()));
}

void Ship::addScore(quint32 score)
{
    _score += score;
    DEBUG("Ship::addScore() : add:" << score << " total:" << _score, true);

    /* Tell the Core that score has changed */
    _scoreChanged = true;
}


//Getter & Setter
quint32 Ship::vie() const
{
    return _vie;
}

void Ship::setVie(quint32 vie)
{
    _vie = vie;
}

quint32 Ship::shipNumber() const
{
    return _shipNumber;
}

void Ship::shipNumber(quint32 shipNumber)
{
    _shipNumber = shipNumber;
}

void Ship::score(quint32 score)
{
    _score = score;
    _scoreChanged = true;
}

quint32 Ship::score() const
{
    return _score;
}

bool Ship::scoreChanged()
{
    bool    ret = _scoreChanged;

    _scoreChanged = false;
    return ret;
}

QPointF Ship::center() const
{
    qint32  x;
    qint32  y;

    x = ((*this)[0].x() + (*this)[1].x() + (*this)[2].x() + (*this)[3].x()) / 4;
    y = ((*this)[0].y() + (*this)[1].y() + (*this)[2].y() + (*this)[3].y()) / 4;
    DEBUG("Ship::center() : " << x << y, false);

    return QPointF(x, y);
}

bool Ship::changeLife(qint32 change)
{
    bool aliveOrNot = true;
    _vie += change;
    if(_vie <= 0)
    {
        aliveOrNot = false;
    }
    DEBUG("Ship::changeLife() : Ship has" << _vie << " life", true);
    return aliveOrNot;
}

bool Ship::makeEntityMove()
{
    Entity::makeEntityMove();
    if(_tempo % 10 == 0)
         decrementSpeed(1);
    _tempo = ( _tempo + 1 ) % 100;
    return true;
}
