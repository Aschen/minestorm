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
                detectShipCollision(*ship, entitiesMap);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void Collision::detectShipCollision(Ship &ship, EntityHash &entitiesMap)
{
    //Pour toutes les entités on regarde si il y a collision avec le vaisseau
    for(QSharedPointer<Entity> &entity : entitiesMap)
    {
        for(QPoint &point: *entity)
        {
            bool collide = ship.containsPoint(point, Qt::OddEvenFill);
            if(collide == true && ship.id() != entity->id())
            {
                switch(entity->type())
                {
                    //Si collision avec un vaisseau on enléve une vie à notre vaisseau passer en paramétre
                    //Si plus de vie on l'ajoute à la liste de suppression
                    case Entity::SHIP:
                    {
                        DEBUG("Collisison::detectShipCollision() collision avec un vaisseau", true);
                        if(!ship.changeLife(-1))
                        {
                            _entitiesToDelete.push_back(ship.id());
                        }
                        break;
                    }

                    //Si collision avec une mine on enléve une vie à notre vaisseau
                    //On ajoute ensuite la mine à la liste de supression
                    case Entity::MINE:
                    {
                        if(!ship.changeLife(-1))
                        {
                            _entitiesToDelete.push_back(entity->id());
                        }
                        _entitiesToDelete.push_back(entity->id());
                        break;
                    }
                    default:
                    {
                        break;
                    }
                    DEBUG("Collision::InCollision:" << collide, false);
                }
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
