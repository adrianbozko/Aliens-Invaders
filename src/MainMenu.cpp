#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include "VideoBoard.h""

MainMenu::MainMenu(int width, int height)
{
    screen_width=width;
    screen_heiht=height;
}


void MainMenu::draw_menu(sf::RenderWindow &window)
{

        easy_op.setPointCount(4);
        easy_op.setPoint(0, sf::Vector2f(111,551));
        easy_op.setPoint(1, sf::Vector2f(451,551));
        easy_op.setPoint(2, sf::Vector2f(451,651));
        easy_op.setPoint(3, sf::Vector2f(111,651));
        easy_op.setFillColor(sf::Color::Black);

        hard_op.setPointCount(4);
        hard_op.setPoint(0, sf::Vector2f(554,551));
        hard_op.setPoint(1, sf::Vector2f(893,551));
        hard_op.setPoint(2, sf::Vector2f(893,651));
        hard_op.setPoint(3, sf::Vector2f(554,651));
        hard_op.setFillColor(sf::Color::Black);

        background1.setPointCount(4);
        background1.setPoint(0, sf::Vector2f(0,0));
        background1.setPoint(1, sf::Vector2f(1000,0));
        background1.setPoint(2, sf::Vector2f(1000,1000));
        background1.setPoint(3, sf::Vector2f(0,1000));
        background1.setTexture(&loading);


        while (window.isOpen())
        {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (event.mouseButton.x >= 112 and event.mouseButton.x <= 450 and event.mouseButton.y >= 552 and event.mouseButton.y <= 651)
                    {
                        level=1;
                        easy_op.setFillColor(sf::Color(244, 195, 34));
                        hard_op.setFillColor(sf::Color::Black);
                    }
                    if (event.mouseButton.x >= 554 and event.mouseButton.x <= 892 and event.mouseButton.y >= 552 and event.mouseButton.y <= 651)
                    {
                        level=2;
                        easy_op.setFillColor(sf::Color::Black);
                        hard_op.setFillColor(sf::Color(244, 195, 34));
                    }
                    if (event.mouseButton.x >= 269 and event.mouseButton.x <= 729 and event.mouseButton.y >= 714 and event.mouseButton.y <= 819)
                    {
                         controller=1;

                    }
                    if (event.mouseButton.x >= 308 and event.mouseButton.x <= 690 and event.mouseButton.y >= 861 and event.mouseButton.y <= 966)
                    {
                        exit(0);
                    }
                }
            }




            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        background.setPointCount(4);
        background.setPoint(0, sf::Vector2f(0,0));
        background.setPoint(1, sf::Vector2f(1000,0));
        background.setPoint(2, sf::Vector2f(1000,1000));
        background.setPoint(3, sf::Vector2f(0,1000));
        background.setTexture(&back_ground);
        window.draw(background);


        window.draw(easy_op);


        easy.setString("EASY");
        easy.setCharacterSize(70);
        easy.setColor(sf::Color::White);
        easy.setFont(font);
        easy.setPosition(185,550);
        window.draw(easy);


        window.draw(hard_op);

        hard.setString("HARD");
        hard.setCharacterSize(70);
        hard.setColor(sf::Color::White);
        hard.setFont(font);
        hard.setPosition(630,550);
        window.draw(hard);

        start.setString("START GAME");
        start.setCharacterSize(65);
        start.setColor(sf::Color::White);
        start.setFont(font);
        start.setPosition(290,723);
        window.draw(start);

        endd.setString("QUIT");
        endd.setCharacterSize(65);
        endd.setColor(sf::Color::White);
        endd.setFont(font);
        endd.setPosition(420,865);
        window.draw(endd);

        window.display();

        sf::Clock Clock;
        sf::Time elapsed;
        double time;
        int mainTimer=0;
        while(mainTimer==0)
            {
                elapsed=Clock.getElapsedTime();
                time=elapsed.asSeconds();
                time=time/1;
                if(time>0.1)
                {
                    mainTimer++;
                    if(controller==1)
                        {
                            loadingTimer++;


                        }
                }
                if(loadingTimer>0 and loadingTimer<30)
                {
                    window.draw(background1);
                    window.display();
                }
                if(loadingTimer>=30)
                {
                    window.close();
                }
                if(mainTimer>=40)
                {
                    mainTimer=0;
                }
            }



        }




}



int MainMenu::returnLevel()
{
    return level;
}


void MainMenu::loadTexture()
{
    back_ground.loadFromFile("image/background.png");
    font.loadFromFile("image/greaseguncond.ttf");
    loading.loadFromFile("image/loadingscreen.jpg");
}
