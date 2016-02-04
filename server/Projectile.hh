#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include <QRect>
#include "Entity.hh"
#include "Ship.hh"

class Projectile : public Entity
{
public:
    //Constructors
    Projectile(qint32, Ship&, QPoint, double);

    //Getters & Setters
    qint32 id() const;
    void setId(const qint32 &id);

    Ship &ship() const;
    void setShip(Ship const &ship);

    QPoint position() const;
    void setPosition(const QPoint &position);

    double angle() const;
    void setAngle(double angle);

    QLine line() const;
    void setLine(const QLine &line);

    //Methods
    void                init();

private:
    qint32              _id;
    Ship&               _ship;
    QPoint              _position;
    double              _angle;
    QLine               _line;
};

#endif // PROJECTILE_HH
