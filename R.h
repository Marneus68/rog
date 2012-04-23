#ifndef __GAME_R_H__
#define __GAME_R_H__

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "constants.h"
#include "palette.h"
#include "Map.h"
#include "Entity.h"

using namespace std;
using namespace sf;

namespace rog
{
    class Rgame
    {
        private:
        /* membres */
        static Rgame *_singleton;
        string m_title;
        /* membres issus de SFML */
        RenderWindow    renderWindow;
        Event           event;
        
        Image           gameWorld;
        
        Sprite          gameWorldSpr,
                        mapSpr;
        
        Shape           gui;
        
        int             scale;
        
        Entity          hero;
        
        Rmap            *newMap;
        
        /* Runtime methods */
        void pre_init(void);
        void init(void);
        void main_loop(void);
        void cleanup(void);
        
        void saySize(void);
        void setWindowScaling(void);
        
        void resolveTurn(int move_x, int move_y);
        void moveEnemy(void);
        void deeper(void);
        void resetMap(void);
        
        // Constructeur
        Rgame(string const& e_title);
        // Destructeur
        virtual ~Rgame(){};
        
        public:
        static Rgame *Initialize(string const& e_title);
        static void kill(void);
        
        void Run(void);
        
        unsigned int randRange(unsigned int a, unsigned int b);
    };
}; /* namespace rog */


#endif /* __GAME_R_H__ */

