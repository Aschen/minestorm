#include "Projectile.hh"

Projectile::Projectile(Ship& ship)
    : Entity(Entity::SHOT), _ship(ship)
{
    this->speed(40);
    this->angle(_ship.angle());
    init();
    _playSound = true;
    _tempo = 0;
    DEBUG("Tir:angle:"<<_angle << ", speed" <<_speed <<", pos" << this->center().x() <<":"<<this->center().y(), false);

}

void Projectile::init()
{

    qreal cX, cY;
    cX = _ship.center().x() + 16 * cos(_ship.getRadian(_angle));
    cY = _ship.center().y() + 16 * sin(_ship.getRadian(_angle));

    DEBUG("Center(" << cX << "," << cY,false);

    QPointF a =  QPointF(cX,cY -6);

    QPointF b = QPointF(cX + 12,cY -6);
    QPointF c = QPointF(cX + 12,cY +6);
    QPointF d = QPointF(cX ,cY + 6);

    this->addPoint(a);
    this->addPoint(b);
    this->addPoint(c);
    this->addPoint(d);

    DEBUG("A(" << a.x() << "," << a.y() << ") - B(" << b.x() << "," << b.y() << ")", false);
    DEBUG("D(" << d.x() << "," << d.y() << ") -C(" << c.x() << "," << c.y() << ")", false);
}

Ship &Projectile::ship() const
{
    return _ship;
}

QPointF Projectile::center() const
{
    qint32  x;
    qint32  y;

    x = ((*this)[0].x() + (*this)[1].x() + (*this)[2].x() + (*this)[3].x()) / 4;
    y = ((*this)[0].y() + (*this)[1].y() + (*this)[2].y() + (*this)[3].y()) / 4;
    DEBUG("Projectile::center() : 2 points :" << x << y, false);
    return QPointF(x, y);
}

bool Projectile::playSound() const
{
    return _playSound;
}

void Projectile::playSound(bool value)
{
    _playSound = value;
}

bool Projectile::makeEntityMove()
{
    bool    ret = false;

    if(_etat == Entity::ALIVE)
    {
        if (this->center().x() > SCREEN_WIDTH
        ||  this->center().y() > SCREEN_HEIGHT
        ||  this->center().y() < 0
        ||  this->center().x() < 0)
        {
            this->setEtatDead();
            ret = false;
        }
        else
        {
            this->translate(_speed * cos(getRadian(_angle)), _speed * sin(getRadian(_angle)));
            ret =  true;
            _tempo++;
            if(_tempo > 1 && _playSound)
                playSound(false);
        }
    }

    return ret;
}
