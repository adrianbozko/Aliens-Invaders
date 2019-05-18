#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>



enum GameMode  { DEBUG, EASY, HARD};
enum GameState { RUNNING, FINISHED_LOSS };

struct Field
{
    bool hasEnemy;
    bool hasPlayer;
    bool hasBullet;
    bool powerUp1;
    bool powerUp2;
};

class GameBoard
{
    public:
        GameBoard(int width, int height, GameMode mode);
        void setField(int x, int y, bool hasEnemy, bool hasPlayer, bool hasBullet, bool powerUp1, bool powerUp2);
        void setBoard();
        void destroyAllEnemies();
        int getBoardWidth();
        int getBoardHeight();
        bool hasEnemy(int x, int y) const;
        bool hasPlayer(int x, int y) const;
        bool hasBullet(int x, int y) const;
        bool isHitted(int x, int y);
        void toggleEnemy(int x, int y);
        void removeEnemy(int x, int y);
        void togglePlayer(int x, int y);
        void removePlayer(int x, int y);
        void toggleBullet(int x, int y);
        void removeBullet(int x, int y);
        GameState getGameState();
        GameMode getGameMode();
        char getFieldInfo(int x, int y);
        void debug_display();
        void moveEnemy();
        void moveBullet();
        void movePlayer(int move);
        int playerXPOS();
        void deployEnemy();
        void setPowerUp();
        void setPowerUp(int x, int y, int type);
        void removePowerUp(int x, int y);
        int hasPowerUp(int x, int y);
        void movePoweUp();
        int playerPowerUpState=0;
        int lives=3;
        int getLivesNumber();
        double getScore();
        double score=0;
        GameState state;
        void load();

    private:
        Field board[100][100];
        int boardWidth;
        int boardHeight;
        GameMode mode;


        sf::SoundBuffer alien_destroyed;
        sf::Sound sound1;
        sf::SoundBuffer player_destroyed;
        sf::Sound sound2;
        sf::SoundBuffer powerup;
        sf::Sound sound3;


};

#endif // GAMEBOARD_H
