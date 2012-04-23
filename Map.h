#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <cstdlib>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "palette.h"
#include "constants.h"
#include "Entity.h"

using namespace std;
using namespace sf;

namespace rog
{
    class Rmap
    {
        private:
        /* membres et methodes */
        int nb_monsters,
            nb_rooms;
        
        Vector2f    startPosition,
                    exitPosition;
        
        Image   *imageMap;
        Sprite  imageMapSpr;
        
        Entity  *monster;
        
        unsigned int randRange(unsigned int a, unsigned int b);
        
        public:
        // Constructeur
        Rmap();
        // Destructeur
        virtual ~Rmap(){};
        // Methodes
        
        Sprite GetSprite(void);
        
        bool isOnTheMap(unsigned int x, unsigned int y);
        bool isBlack(unsigned int x, unsigned int y);
        bool isCorridor(unsigned int x, unsigned int y);
        
        Entity *getMonster(void);
        
        Vector2f GetStartPosition(void);
    };
}; /* namespace rog */

#endif /* __MAP_H__ */

