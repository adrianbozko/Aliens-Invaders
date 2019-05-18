#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameBoard.h"
#include "VideoBoard.h"
#include "MainMenu.h"

int main()
{
    int x0 = 100;
    int y0 = 50;

    int field_x= 50;
    int field_y= 45;

    int window_width = 1000;
    int window_height = 1000;
    GameMode difficulty=EASY;
    int open_checker=0;

    sf::Music main;
    main.openFromFile("sounds/menutheme.ogg");
    main.setVolume(10.f);

    if(open_checker==0)
    {
        sf::RenderWindow window(sf::VideoMode(window_width,window_height), "Aliens Invader Main Menu");
        MainMenu menu(window_width,window_height);
        menu.loadTexture();
        main.play();
        menu.draw_menu(window);
        open_checker=1;
        if(menu.returnLevel()==1)
            difficulty=EASY;
        if(menu.returnLevel()==2)
            difficulty=HARD;
    }
    main.stop();
    sf::Music game;
    game.openFromFile("sounds/gametheme.ogg");
    GameBoard AliensInvader(5,20,difficulty);
    AliensInvader.load();
    sf::RenderWindow window(sf::VideoMode(window_width,window_height), "Aliens Invader");
    VideoBoard view(AliensInvader,x0,y0,field_x, field_y);
    view.loadTextures();
    game.play();
    view.play(window);
    game.stop();

/*  GameBoard AliensInvader(3,11,DEBUG);
    AliensInvader.debug_display();
    sf::Clock Clock;
    sf::Time elapsed;
    AliensInvader.moveEnemy();
    AliensInvader.debug_display();
    AliensInvader.moveBullet();
    AliensInvader.debug_display();
    AliensInvader.moveEnemy();
    AliensInvader.debug_display();
    AliensInvader.moveEnemy();
    AliensInvader.moveEnemy();
    AliensInvader.moveEnemy();
    AliensInvader.debug_display();
    std::cout << AliensInvader.getGameState() << std::endl;
    AliensInvader.moveEnemy();
    AliensInvader.debug_display();
    std::cout << AliensInvader.getGameState() << std::endl;
*/    return 0;
}
