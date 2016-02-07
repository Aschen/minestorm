#ifndef COLLISION_HH
#define COLLISION_HH

# include <QPoint>

# include "Entity.hh"
# include "Ship.hh"
# include "Mine.hh"
# include "Minestorm.hh"

class Collision
{
private:
    QVector<int>        _entitiesToDelete;

public:
    Collision(EntityHash &entitiesMap);
    void                detectCollision(EntityHash &entitiesMap);
    void                detectShipCollision(Ship &ship, EntityHash &entitiesMap);
    void                detectMineCollision(Mine &mine, EntityHash &entitiesMap);
    void                removeEntities(EntityHash &entitiesMap);
};

#endif // COLLISION_HH
