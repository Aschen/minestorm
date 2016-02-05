#include "Collision.hh"

Collision::Collision(EntityHash &entitiesMap)
{
    detectCollision(entitiesMap);
    removeEntities(entitiesMap);
}

void Collision::detectCollision(EntityHash &entitiesMap)
{
    for(QSharedPointer<Entity> &entity : entitiesMap)
    {
        switch(entity->type())
        {
        case Entity::SHIP:
        {
            Ship *ship = dynamic_cast<Ship*>(entity.data());
            for(QSharedPointer<Entity> &entity2 : entitiesMap)
            {
                for(QPoint &point: *entity2)
                {
                    bool collide = ship->containsPoint(point, Qt::OddEvenFill);
                    if(collide == true && ship->id() != entity2->id())
                    {
                        _entitiesToDelete.push_back(entity->id());
                    }
                    DEBUG("Collision::InCollision:" << collide, true);
                }
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

void Collision::removeEntities(EntityHash &entitiesMap)
{
    for(int id: _entitiesToDelete)
    {
        entitiesMap.remove(id);
    }
}
