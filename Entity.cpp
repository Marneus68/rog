#include "Entity.h"

namespace rog
{
    Entity::Entity(unsigned int e_x, unsigned int e_y, unsigned int e_max_life, unsigned int e_max_xp) : 
        x(e_x),
        y(e_y),
        life(e_max_life),
        max_life(e_max_life),
        xp(0),
        max_xp(e_max_xp),
        level(1)
    {
        
    }
    
    Entity::Entity() : 
        x(1),
        y(1),
        life(5),
        max_life(5),
        xp(0),
        max_xp(10),
        level(1)
    {
        
    }
    
    void Entity::hurt(unsigned int e_damages)
    {
        if (life)
            life-=e_damages;
    }
    
    bool Entity::isDead(void)
    {
        if (life)
            return false;
        else
            return true;
    }
    
    void Entity::gainXp(void)
    {
        xp++;
        if (checkForNewLevel()) levelUp();
    }
    
    void Entity::gainXp(unsigned int e_xp)
    {
        xp+=e_xp;
        checkForNewLevel();
    }
    
    bool Entity::checkForNewLevel(void)
    {
        if (xp >= max_xp)
            levelUp();
    }
    
    void Entity::levelUp(void)
    
    {
        xp = 0;
        level++;
    }
    
    unsigned int Entity::getDamages()
    {
        return (xp / 3);
    }
    
    unsigned int Entity::getLife()
    {
        return life;
    }
    
    unsigned int Entity::getXp()
    {
        return xp;
    }
    
    unsigned int Entity::getLevel()
    {
        return level;
    }
}; /* namespace rog */

