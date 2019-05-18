#ifndef VIDEOBOARD_H
#define VIDEOBOARD_H
#include "GameBoard.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class VideoBoard
{
    public:
        VideoBoard(GameBoard &Aliens, int x0, int y0, int lenght, int fy);
        void draw_board(sf::RenderWindow &window);
        void loadTextures();
        void play(sf::RenderWindow &window);

    private:
        int enemyTimer=0;
        int enemyDeployTime=5;
        int powerUpTimer=0;
        int slowTimeCount=0;
        int slowTimeTime=0;
        GameBoard &board;
        int board_width;
        int board_height;
        int field_lenght;
        int field_y;
        int x0;
        int y0;
        sf::ConvexShape pole;
        sf::ConvexShape pole1;
        sf::ConvexShape pole2;
        sf::ConvexShape background;
        sf::ConvexShape powerups;
        void VsetEnemy(sf::RenderWindow &window, int x, int y);
        void VsetPlayer(sf::RenderWindow &window, int x, int y);
        void VsetBullet(sf::RenderWindow &window, int x, int y);
        void VsetBoom(sf::RenderWindow &window, int x, int y);
        void VsetPU1(sf::RenderWindow &window, int x, int y);
        void VsetPU2(sf::RenderWindow &window, int x, int y);
        void VdrawLivesNumber(sf::RenderWindow &window, int x, int y, int i);
        void EndGameScreen(sf::RenderWindow &window);
        void VdrawPowerUp(sf::RenderWindow &window, int status);
        void VdrawScore(sf::RenderWindow &window, int x, int y);

        sf::Texture heart;
        sf::Texture alien1;
        sf::Texture alien2;
        sf::Texture powerup;
        sf::Texture powerup1;
        sf::Texture powerup2;
        sf::Texture fire;
        sf::Texture player;
        sf::Texture laser;
        sf::Texture back_ground;
        sf::Texture endgame;
        sf::Font font;

        sf::SoundBuffer fire_sound;

        sf::Sound sound;



};

#endif // VIDEOBOARD_H
