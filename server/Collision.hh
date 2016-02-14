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
    EntitiesHash          _entitiesMap;

public:
    Collision(EntitiesHash &entitiesMap);

    bool                checkCollision(Entity &entity1, Entity &entity2);
    void                detectShipCollision(QSharedPointer<Entity> &shipEntity);
    void                detectMineCollision(QSharedPointer<Entity> &mineEntity);
};

#endif // COLLISION_HH
