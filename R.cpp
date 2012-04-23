#include "R.h"

namespace rog
{
    Rgame *Rgame::_singleton = NULL;
    
    void Rgame::pre_init(void)
    {
        cout << m_title  << " is starting." << endl;
        
        renderWindow.Create(VideoMode(SCREEN_W, SCREEN_H),
                m_title,Style::Resize | Style::Close);
        
        renderWindow.UseVerticalSync(true);
        
        renderWindow.SetFramerateLimit(30);
        
        scale = 1;
    }
    
    void Rgame::init(void)
    {
        gameWorld = Image(SCREEN_W, SCREEN_H, Color::Black);
        
        gui = Shape::Rectangle(0, 0, SCREEN_W, 3, color::interface);
        
        gameWorldSpr.SetImage(gameWorld);
        
        // Initialisation des valeurs
        hero = Entity(0, 0, 5, 10);
        
        Vector2f Center(SCREEN_W/2, SCREEN_H/2);
    }
    
    void Rgame::main_loop(void)
    {
        newMap = new Rmap();
        mapSpr = newMap->GetSprite();
        
        while (mapSpr.GetPixel(hero.x, hero.y) == Color::Black)
        {
            hero.x = randRange(0, mapSpr.GetSize().x);
            hero.y = randRange(0, mapSpr.GetSize().y);
        }
        
        
        
        while (renderWindow.IsOpened())
        {
            // Process events
            while (renderWindow.GetEvent(event))
            {
                switch (event.Type)
                {
                    case Event::Closed:
                        // Fermeture de l'application en cas de fermeture
                        renderWindow.Close();
                        break;
                    
                    case Event::KeyPressed:
                        // Pression d'une touche
                        switch (event.Key.Code)
                        {
                            case Key::Escape:
                                renderWindow.Close();
                                break;
                            case Key::F1:
                                scale = 1;
                                setWindowScaling();
                                saySize();
                                break;
                            case Key::F2:
                                scale = 3;
                                setWindowScaling();
                                saySize();
                                break;
                            case Key::F3:
                                scale = 6;
                                setWindowScaling();
                                saySize();
                                break;
                            case Key::F4:
                                scale = 9;
                                setWindowScaling();
                                saySize();
                                break;
                                
                            case Key::Up:
                                resolveTurn(0,-1);
//                                if (mapSpr.GetPixel(hero.x, hero.y-1) == color::exit)
//                                    deeper();
//                                
//                                if ((mapSpr.GetPixel(hero.x, hero.y-1) != Color::Black) || (hero.y-1 == 0))
//                                    hero.y--;
                                break;
                            case Key::Down:
                                resolveTurn(0,1);
//                                if (mapSpr.GetPixel(hero.x, hero.y+1) == color::exit)
//                                    deeper();
//                                
//                                if ((mapSpr.GetPixel(hero.x, hero.y+1) != Color::Black) || (hero.y+1 == SCREEN_H))
//                                    hero.y++;
                                break;
                            case Key::Right:
                                resolveTurn(1,0);
//                                if (mapSpr.GetPixel(hero.x+1, hero.y) == color::exit)
//                                    deeper();
//                                
//                                if ((mapSpr.GetPixel(hero.x+1, hero.y) != Color::Black) || (hero.x+1 == SCREEN_W))
//                                    hero.x++;
                                break;
                            case Key::Left:
                                resolveTurn(-1,0);
//                                if (mapSpr.GetPixel(hero.x-1, hero.y) == color::exit)
//                                    deeper();
//                                
//                                if ((mapSpr.GetPixel(hero.x-1, hero.y) != Color::Black) || (hero.x-1 == 0))
//                                    hero.x--;
                                break;
                        }
                        break;
                }
            }
            
            renderWindow.Clear(Color::Black);
            
            renderWindow.Draw(gui);
            
            // Affichage des bares
            // Bare de vie
            Shape lifebar = Shape::Rectangle(0, 0, hero.getLife(), 1, color::life);
            renderWindow.Draw(lifebar);
            // Bare d'experience
            Shape xpbar = Shape::Rectangle(0, 2, hero.getXp(), 3, color::experience);
            renderWindow.Draw(xpbar);
            // Bare de niveaux
            Shape levelbar = Shape::Rectangle(SCREEN_W - hero.getLevel(), 2, SCREEN_W, 3, color::level);
            renderWindow.Draw(levelbar);
            
            mapSpr = newMap->GetSprite();
            renderWindow.Draw(mapSpr);
            
            // Dessine le heros
            Shape heroShape = Shape::Rectangle(hero.x, hero.y+3, hero.x+1, hero.y+1+3, color::hero);
            mapSpr.SetX(hero.x);
            mapSpr.SetY(hero.y);
            renderWindow.Draw(heroShape);
            
            // Dessine les monstres
            Shape monsterShape = Shape::Rectangle(newMap->getMonster()->x, newMap->getMonster()->y+3, newMap->getMonster()->x+1, newMap->getMonster()->y+1+3, color::enemy);
            renderWindow.Draw(monsterShape);
            
            renderWindow.Display();
        }
    }
    
    void Rgame::cleanup(void)
    {
        
    }
    
        Rgame::Rgame(string const& e_title) : 
        m_title(e_title)
    {
        // Rien à faire
    }
    
    // Public
    Rgame* Rgame::Initialize(string const& e_title)
    {
        if (_singleton == NULL)
        {
            _singleton =  new Rgame(e_title);
        }
        else
        {
            // Rien à faire
        }
        return _singleton;
    }
    
    void Rgame::kill(void)
    {
        if (_singleton != NULL)
        {
            delete _singleton;
            _singleton = NULL;
        }
    }    
    
    void Rgame::Run(void)
    {
        pre_init();
        init();
        main_loop();
        cleanup();
        
        return;
    }
    
    void Rgame::saySize(void)
    {
        cout << "Game window sized to " << renderWindow.GetWidth() << ", " << renderWindow.GetHeight() << endl;
    }
    
    void Rgame::setWindowScaling(void)
    {
        renderWindow.SetSize(SCREEN_W * scale, SCREEN_H * scale);
    }
    
    unsigned int Rgame::randRange(unsigned int a, unsigned int b)
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
    
    void Rgame::resolveTurn(int move_x, int move_y)
    {
        if (mapSpr.GetPixel(hero.x+move_x, hero.y+move_y) == color::exit)
            deeper();
            
        if (mapSpr.GetPixel(hero.x+move_x, hero.y+move_y) != Color::Black)
        {
            hero.x+=move_x;
            hero.y+=move_y;
        }
        
        moveEnemy();
    }
    
    void Rgame::moveEnemy(void)
    {
//        if (newMap->getMonster->isDead())
//        {
//        
//        }
    }
    
    void Rgame::deeper(void)
    {
        resetMap();
        hero.gainXp(2);
    }
    
    void Rgame::resetMap(void)
    {
        newMap = new Rmap();
        mapSpr = newMap->GetSprite();
        
        while (mapSpr.GetPixel(hero.x, hero.y) == Color::Black)
        {
            hero.x = randRange(0, mapSpr.GetSize().x);
            hero.y = randRange(0, mapSpr.GetSize().y);
        }
    }
}; /* namespace rog */

