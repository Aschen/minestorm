#include "Collision.hh"

Collision::Collision(EntityHash &entitiesMap, EntityVector &entitiesToDelete)
    : _entitiesMap(entitiesMap),
      _entitiesToDelete(entitiesToDelete)
{
    detectCollision();
}

void Collision::detectCollision()
{
    for(QSharedPointer<Entity> &entity : _entitiesMap)
    {
        switch(entity->type())
        {
            case Entity::SHIP:
            {
                detectShipCollision(entity);
                break;
            }
            case Entity::MINE:
            {
                detectMineCollision(entity);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void Collision::detectShipCollision(QSharedPointer<Entity> &shipEntity)
{
    Ship *ship = dynamic_cast<Ship*>(shipEntity.data());

    //Pour toutes les entités on regarde si il y a collision avec le vaisseau
    for(QSharedPointer<Entity> &entity : _entitiesMap)
    {
        if(ship->id() != entity->id() && entity->etat() == Entity::ALIVE)
        {
            for(QPointF &point: *entity)
            {
                bool collide = ship->containsPoint(point, Qt::OddEvenFill);
                DEBUG("Collision::detectShipCollision() collision vaisseau : " << collide, false);
                if(collide)
                {
                    DEBUG("Collision::detectShipCollision()  Collision Vaisseau ", false);
                    //On enléve une vie au vaisseau dans tous les cas
                    if(!ship->changeLife(-1))
                    {
                        ship->setEtatDead();
                        _entitiesToDelete.push_back(shipEntity);
                    }
                    //Si l'entité n'est pas un vaisseau on l'ajoute à la liste de supression
                    if(entity->type() != Entity::SHIP)
                    {
                        entity->setEtatDead();
                        _entitiesToDelete.push_back(entity);
                    }
                    break;
                }
            }
        }
    }
}

void Collision::detectMineCollision(QSharedPointer<Entity> &mineEntity)
{
    Mine *mine = dynamic_cast<Mine*>(mineEntity.data());

    for(QSharedPointer<Entity> &entity : _entitiesMap)
    {
        //Si l'entité est un tir et qu'il y a collision on supprime les deux (tir & mine)
        if(entity->type() == Entity::SHOT && entity->etat() == 1)
        {
            for(QPointF &point: *entity)
            {
                bool collide = mine->containsPoint(point, Qt::OddEvenFill);
                if(collide == true)
                {
                    mine->setEtatDead();
                    entity->setEtatDead();
                    _entitiesToDelete.push_back(mineEntity);
                    _entitiesToDelete.push_back(entity);
                }
            }
        }
    }
}
