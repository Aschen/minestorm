#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include <QRect>
#include "Entity.hh"

class Ship;

using namespace std;

class Projectile : public Entity
{
public:
    //Constructors
    Projectile(qint32, Ship&);

    //Getters & Setters
    qint32      id() const;
    void        setId(const qint32 &id);

    Ship        &ship() const;

    QPolygonF   body() const;
    void        setBody(const QPolygonF &body);

    //Methods
    void        init();

private:
    qint32       _id;
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
