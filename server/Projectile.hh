#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include <QRect>
#include "Entity.hh"

class Ship;

class Projectile : public Entity
{
public:
    //Constructors
    Projectile(Ship&);

    Ship        &ship() const;

    QPolygonF   body() const;
    void        setBody(const QPolygonF &body);

    //Methods
    void        init();

private:
    Ship&        _ship;

    // Entity interface
public:
    QPointF      center() const override;

    // Entity interface
public:
    bool        makeEntityMove() override;
};

#endif // PROJECTILE_HH

#include "Ship.hh"
