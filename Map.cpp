#include "Map.h"

namespace rog
{
    Rmap::Rmap() :
        nb_monsters(randRange(3,6)),
        nb_rooms(randRange(8,10))
    {
        cout << "Creating a new tiny world with " << nb_rooms << " rooms." << endl;
        
        imageMap = new Image(SCREEN_W, SCREEN_H-4, Color::Black);
        imageMap->SetSmooth(false);
        
        for (int i = 0; i < nb_rooms; i++)
        {
            Vector2f newRoom(randRange(3,8), randRange(3,8));
            cout << "Room " << i+1 << " is " << newRoom.x << " by " << newRoom.y << " pixels big." << endl;
            
            Vector2f placement;
            do
            {
                placement = Vector2f(randRange(2,SCREEN_W-newRoom.x), randRange(2, SCREEN_H-newRoom.y));
            }
            while   ((isOnTheMap(placement.x, placement.y)) ||
                    (isOnTheMap(placement.x + newRoom.x, placement.y + newRoom.y)) ||
                    (isOnTheMap(placement.x, placement.y + newRoom.y)) ||
                    (isOnTheMap(placement.x + newRoom.x, placement.y)));
            
            cout << "Placing room " << i+1 << " at " << placement.x << ", " << placement.y << "..."<< endl;
            imageMap->SetPixel(placement.x,placement.y, color::room);
            
            int x, y;
            for (x = 0; x < newRoom.x; x++)
            {
                for (y = 0; y < newRoom.y; y++)
                {
                    imageMap->SetPixel(placement.x + x,placement.y - y, color::room);
                }
            }
        }
        
        do
        {
            startPosition = Vector2f(randRange(0,SCREEN_W), randRange(3, SCREEN_H));
        }
        while (!isOnTheMap(startPosition.x, startPosition.y));
        
        cout << "Starting point placed at " << startPosition.x << ", " << startPosition.y << endl;
        
        do
        {
            exitPosition = Vector2f(randRange(0,SCREEN_W), randRange(3, SCREEN_H));
        }
        while (!isOnTheMap(exitPosition.x, exitPosition.y));
        imageMap->SetPixel(exitPosition.x,exitPosition.y, color::exit);
        
        cout << "Exit point placed at " << exitPosition.x << ", " << exitPosition.y << endl;
        
        // Placement du monstre
        Vector2f placementMonster;
        do
        {
            placementMonster = Vector2f(randRange(2,imageMap->GetWidth()), randRange(2, imageMap->GetHeight() ));
        }
        while   (!isOnTheMap(placementMonster.x, placementMonster.y));
        
        monster = new Entity(placementMonster.x,placementMonster.y,5,10);
        
        imageMapSpr.SetX(0);
        imageMapSpr.SetY(3);
        
        
        // TODO: dessin des couloirs
        for (int i = 0; i < nb_rooms; i++)
        {
            Vector2f newCoridorPos;
            do
            {
                newCoridorPos = Vector2f(randRange(0,SCREEN_W), randRange(3, SCREEN_H));
            }
            while (!isOnTheMap(newCoridorPos.x, newCoridorPos.y));
            
            unsigned int direction = randRange(0, 3);
            
            int direct_x,
                direct_y;
            
            switch (direction)
            {
                case 0:
                    direct_x = 1;
                    direct_y = 0;
                    break;
                case 1:
                    direct_x = 0;
                    direct_y = 1;
                    break;
                case 2:
                    direct_x = 0;
                    direct_y = -1;
                    break;
                case 3:
                    direct_x = -1;
                    direct_y = 0;
                    break;
            }
            
            int next_x = newCoridorPos.x,
                next_y = newCoridorPos.y;
            
            bool stop;
            while ((next_x < imageMap->GetWidth() - 2) && (next_y < imageMap->GetHeight() - 2) && next_y && next_x && stop)
            {
                bool    leftInitialRoom = 0;
                
                if ((leftInitialRoom && (isOnTheMap(next_x, next_y) && !isOnTheMap(next_x + direct_x, next_y + direct_y)) && !stop) || 
                    isCorridor(next_x, next_y+1) || 
                    isCorridor(next_x, next_y-1) || 
                    isCorridor(next_x+1, next_y) || 
                    isCorridor(next_x-1, next_x))
                {
                    stop = 1;
                }
                
                if (isOnTheMap(next_x, next_y) && !isOnTheMap(next_x + direct_x, next_y + direct_y) && !leftInitialRoom)
                    leftInitialRoom = !leftInitialRoom;
                
                if (isBlack(next_x + direct_x, next_y + direct_y))
                {
                    imageMap->SetPixel(next_x + direct_x, next_y + direct_y, color::coridor);
                }
                
                next_x += direct_x;
                next_y += direct_y;
            }
            
        }
        
        
        imageMapSpr.SetImage(*imageMap);
    }
    
    unsigned int Rmap::randRange(unsigned int a, unsigned int b)
    {
        if (a < b)
        {
            unsigned int c = b - a;
            unsigned int r = ((rand()%c)+a);
            return r;
        }
        else if (a > b)
        {
            unsigned int c = a - b;
            unsigned int r = ((rand()%c)+b);
            return r;
        }
        else
        {
            return a;
        }
    }
    
    Sprite Rmap::GetSprite(void)
    {
        return imageMapSpr;
    }
    
    bool Rmap::isOnTheMap(unsigned int x, unsigned int y)
    {
        bool ret = 0;
        
        if (x < imageMap->GetWidth() && y < imageMap->GetHeight())
        {
            ret = imageMap->GetPixel(x, y) != Color::Black;
        }
        
        return ret;
    }
    
    bool Rmap::isBlack(unsigned int x, unsigned int y)
    {
        bool ret = 0;
        
        if (x < imageMap->GetWidth() && y < imageMap->GetHeight())
        {
            ret = imageMap->GetPixel(x, y) == Color::Black;
        }
        
        return ret;
    }
    
    bool Rmap::isCorridor(unsigned int x, unsigned int y)
    {
        bool ret = 0;
        
        if (x < imageMap->GetWidth() && y < imageMap->GetHeight())
        {
            ret = imageMap->GetPixel(x, y) == color::coridor;
        }
        
        return ret;
    }
    
    Vector2f Rmap::GetStartPosition(void)
    {
        return startPosition;
    }
    
    Entity* Rmap::getMonster(void)
    {
        return monster;
    }
}; /* namespace rog */

