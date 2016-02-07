#ifndef PROJECTILE_HH
#define PROJECTILE_HH

#include <QRect>
#include "Entity.hh"
#include "Ship.hh"

using namespace std;

class Projectile : public Entity
{
public:
    //Constructors
    Projectile(qint32, Ship&);

    //Getters & Setters
    qint32 id() const;
    void setId(const qint32 &id);

    Ship &ship() const;

    QPolygon body() const;
    void setBody(const QPolygon &body);

    //Methods
    void                init();

private:
    qint32              _id;
    Ship&               _ship;

    // Entity interface
public:
    QPoint center() const override;
};

#endif // PROJECTILE_HH
