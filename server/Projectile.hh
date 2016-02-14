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
    Ship&       _ship;
    bool        _playSound;
    qint32      _tempo;

    // Entity interface
public:
    QPointF     center() const override;
    bool        playSound() const;
    void        playSound(bool value);

    // Entity interface
public:
    bool        makeEntityMove() override;
};

#endif // PROJECTILE_HH

#include "Ship.hh"
