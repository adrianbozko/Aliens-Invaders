#ifndef MAINMENU_H
#define MAINMENU_H
#include <SFML/Graphics.hpp>


class MainMenu
{
    public:
        MainMenu(int width, int height);
        void draw_menu(sf::RenderWindow &window);
        void loadTexture();
        int level=0;
        int returnLevel();

    private:
        int controller=0;
        int loadingTimer=0;
        int screen_width;
        int screen_heiht;
        sf::ConvexShape background;
        sf::ConvexShape background1;
        sf::Texture back_ground;
        sf::Texture loading;
        sf::Font font;
        sf::Text easy;
        sf::Text hard;
        sf::Text start;
        sf::Text endd;

        sf::ConvexShape easy_op;
        sf::ConvexShape hard_op;


};

#endif // MAINMENU_H
