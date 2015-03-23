#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include <string>
 
#include "game.h"

#define WIDTH_SCREEN 640
#define HEIGTH_SCREEN 640
#define SPEED 30 //low is faster



void drawMap(Game* game, std::vector<std::vector<int> > screen);

int main()
{
    Game* game = new Game(WIDTH_SCREEN, HEIGTH_SCREEN);
    sf::Clock time;
    while (game->app.isOpen())
    {
        sf::Event event;
        while (game->app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                game->app.close();
           
        }
        if(!game->getState())
        {   
            game->ia();
            game->run();
        }
        else if (game->getState())
            if(game->getState() == 1) 
                game->gameOver();
            else game->win();
        game->drawMap();
        game->app.display();
        game->app.clear();
    }

    return 0;
}



