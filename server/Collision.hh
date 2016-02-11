#ifndef COLLISION_HH
#define COLLISION_HH

# include <QPoint>

# include "Entity.hh"
# include "Ship.hh"
# include "Projectile.hh"
# include "Mine.hh"
# include "Minestorm.hh"

class Collision
{
private:
    EntityHash          &_entitiesMap;
    EntityVector        &_entitiesToDelete;

public:
    Collision(EntityHash &entitiesMap, EntityVector &entitiesToDelete);


    void                detectCollision();
    void                detectShipCollision(QSharedPointer<Entity> &shipEntity);
    void                detectMineCollision(QSharedPointer<Entity> &mineEntity);
};

#endif // COLLISION_HH
