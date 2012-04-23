#ifndef __ENTITY_H__
#define __ENTITY_H__

namespace rog
{
    class Entity
    {
        private:
        unsigned int    life,
                        max_life,
                        xp,
                        max_xp,
                        level;
    
        public:
        unsigned int    x,
                        y;
        // Constructeur
        Entity(unsigned int e_x, unsigned int e_y, unsigned int e_max_life, unsigned int e_max_xp);
        Entity();
        // Destructeur
        virtual ~Entity(void){};
        
        // Methodes
        virtual void hurt(unsigned int e_damages);
        virtual bool isDead(void);
        
        virtual void gainXp(void);
        virtual void gainXp(unsigned int e_xp);
        virtual bool checkForNewLevel(void);
        virtual void levelUp(void);
        
        virtual unsigned int getDamages();
        virtual unsigned int getLife();
        virtual unsigned int getXp();
        virtual unsigned int getLevel();
    };
}; /* namespace rog */

#endif /* __ENTITY_H__ */

