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
            case Entity::MINE:
            {
                Mine *mine = dynamic_cast<Mine*>(entity.data());
                detectMineCollision(*mine, entitiesMap);
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
        if(ship.id() != entity->id() && entity->etat() == 1)
        {
            for(QPointF &point: *entity)
            {
                bool collide = ship.containsPoint(point, Qt::OddEvenFill);
                if(collide)
                {
                    //On enléve une vie au vaisseau dans tous les cas
                    if(!ship.changeLife(-1))
                    {
                        ship.setEtat(0);
                        _entitiesToDelete.push_back(ship.id());
                    }
                    //Si l'entité n'est pas un vaisseau on l'ajoute à la liste de supression
                    if(entity->type() != Entity::SHIP)
                    {
                        entity->setEtat(0);
                        _entitiesToDelete.push_back(entity->id());
                    }
                    break;
                }
            }
        }
    }
}

void Collision::detectMineCollision(Mine &mine, EntityHash &entitiesMap)
{
    for(QSharedPointer<Entity> &entity : entitiesMap)
    {
        //Si l'entité est un tir et qu'il y a collision on supprime les deux (tir & mine)
        if(entity->type() == Entity::SHOT && entity->etat() == 1)
        {
            for(QPointF &point: *entity)
            {
                bool collide = mine.containsPoint(point, Qt::OddEvenFill);
                if(collide == true)
                {
                    _entitiesToDelete.push_back(mine.id());
                    _entitiesToDelete.push_back(entity->id());
                }
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
