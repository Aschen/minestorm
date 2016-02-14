#include "Collision.hh"

Collision::Collision(EntitiesHash &entitiesMap)
    : _entitiesMap(entitiesMap)
{
}



bool Collision::checkCollision(Entity &entity1, Entity &entity2)
{
    bool result = false;
    for(QPointF &point: entity2)
    {
        bool collide = entity1.containsPoint(point, Qt::OddEvenFill);
        DEBUG("Collision::detectShipCollision() collision vaisseau : " << collide, false);
        if(collide)
        {
            result = true;

            //Si l'entité n'est pas un vaisseau on la kill
            if(entity2.type() != Entity::SHIP)
            {
                entity2.setEtatDead();
            }
            break;
        }
    }

    return result;
}

void Collision::detectShipCollision(QSharedPointer<Entity> &shipEntity)
{
    Ship *ship = dynamic_cast<Ship*>(shipEntity.data());

    if(ship->etat() == Entity::ALIVE)
    {
        //Pour tous les vaisseau on regarde si il y a collision avec le vaisseau
        for(QSharedPointer<Entity> &entity : _entitiesMap[Entity::SHIP])
        {
            if(ship != entity.data() && entity->etat() == Entity::ALIVE)
            {
                if(checkCollision(*shipEntity.data(), *entity))
                {
                    ship->changeLife(-1);
                    break;
                }
            }
        }

        //Pour toutes les mines on regarde si il y a collision avec le vaisseau
        for(QSharedPointer<Entity> &entity : _entitiesMap[Entity::MINE])
        {
            if(entity->etat() == Entity::ALIVE)
            {
                if(checkCollision(*shipEntity.data(), *entity))
                {
                    ship->changeLife(-1);
                    break;
                }
            }
        }

        //Pour tous les tirs on regarde si il y a collision avec le vaisseau
        for(QSharedPointer<Entity> &entity : _entitiesMap[Entity::SHOT])
        {
            Projectile *tir = dynamic_cast<Projectile*>(entity.data());
            if(tir->ship() != *ship && entity->etat() == Entity::ALIVE)
            {
                if(checkCollision(*shipEntity.data(), *entity))
                {
                    DEBUG("Collision::detectShipCollision() collision vaisseau tir", false);
                    if(ship->changeLife(-1))
                    {
                        //Add score to the ship who shot
                        dynamic_cast<Projectile*>(entity.data())->ship().addScore(SCORE_SHIP);
                        break;
                    }
                }
            }
        }
    }
}

void Collision::detectMineCollision(QSharedPointer<Entity> &mineEntity)
{
    Mine *mine = dynamic_cast<Mine*>(mineEntity.data());

    for(QSharedPointer<Entity> &entity : _entitiesMap[Entity::SHOT])
    {
        //Si l'entité est un tir et qu'il y a collision on supprime les deux (tir & mine)
        if(entity->etat() == Entity::ALIVE)
        {
            if(checkCollision(*mineEntity.data(), *entity))
            {
                //Add score to the ship who shot
                if (mine->typeMine () != Mine::Exploded)
                    dynamic_cast<Projectile*>(entity.data())->ship().addScore(SCORE_MINE);

                mine->setEtatDead();
                break;
            }
        }
    }
}
