#include "GameBoard.h"


GameBoard::GameBoard(int width, int height, GameMode mode)
{
    boardWidth=width;
    boardHeight=height;
    GameBoard::mode=mode;
    state=RUNNING;
    setBoard();
}

void GameBoard::setField(int x, int y, bool hasEnemy, bool hasPlayer, bool hasBullet, bool powerUp1, bool powerUp2)
{
    board[y][x]={hasEnemy, hasPlayer, hasBullet, powerUp1, powerUp2};
}

int GameBoard::playerXPOS()
{
    for(int i=0;i<boardWidth;i++)
    {
        if(hasPlayer(i,boardHeight-1)==1)
            return i;
    }
}

void GameBoard::movePlayer(int move)
{
    if(state==FINISHED_LOSS)
        return;
    if(move==2)
    {
        if(playerXPOS()==0)
            {
                return;
            }
        else
            {
            int pos=playerXPOS();
            removePlayer(playerXPOS(),boardHeight-1);
            togglePlayer(pos-1,boardHeight-1);

            }
    }
    if(move==1)
    {
        if(playerXPOS()==boardWidth-1)
            return;
        else
        {
            togglePlayer(playerXPOS()+1,boardHeight-1);
            removePlayer(playerXPOS(),boardHeight-1);
        }
    }

}

void GameBoard::setBoard()
{

    if(state==FINISHED_LOSS)
        return;
    for (int idx_y = 0; idx_y < boardHeight; idx_y++) {
        for (int idx_x = 0; idx_x < boardWidth; idx_x++) {
            setField(idx_x, idx_y, false, false, false, false, false);
            }
        }
    setField(boardWidth/2,boardHeight-1,false,true,false, false,false);
}

int GameBoard::getBoardWidth()
{
    return boardWidth;
}

int GameBoard::getBoardHeight()
{
    return boardHeight;
}

bool GameBoard::hasEnemy(int x, int y) const
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return false;
    if(board[y][x].hasEnemy==true)
        return true;
    else return false;
}

bool GameBoard::hasPlayer(int x, int y) const
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return false;
    if(board[y][x].hasPlayer==true)
        return true;
    else return false;
}

bool GameBoard::hasBullet(int x, int y) const
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return false;
    if(board[y][x].hasBullet==true)
        return true;
    else return false;
}
bool GameBoard::isHitted(int x, int y)
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return false;
    if(board[y][x].hasPlayer==true and board[y][x].hasEnemy==true)
        {
            removeEnemy(x,y);
            lives--;
            sound2.play();
            if(lives==0)
            {
                state=FINISHED_LOSS;
                return false;
            }
        }
    if(board[boardHeight-1][x].hasEnemy==true)
        {
            removeEnemy(x,y);
            lives--;
            sound2.play();
            if(lives==0)
            {
                state=FINISHED_LOSS;
                return false;
            }
        }
    if(board[y][x].hasPlayer==true and (board[y][x].powerUp1==1 or board[y][x].powerUp2==1))
        {
            if(board[y][x].powerUp1==1)
            {
                playerPowerUpState=1;
                sound3.play();
                std::cout << "Ustawiono playerPowerUpstate: 1" << std::endl;
            }
            if(board[y][x].powerUp2==1)
            {
                playerPowerUpState=2;
                sound3.play();
                std::cout << "Ustawiono playerPowerUpstate: 2" << std::endl;
            }
            removePowerUp(x,y);

        }

    if(board[y][x].hasEnemy==true and board[y][x].hasBullet==true)
        {

            sound1.play();
            removeEnemy(x,y);
            removeBullet(x,y);
            score=score+10;
            return true;
        }
    else return false;
}

void GameBoard::load()
{
    alien_destroyed.loadFromFile("sounds/invaderkilled.wav");
    sound1.setBuffer(alien_destroyed);
    sound1.setVolume(5.f);
    player_destroyed.loadFromFile("sounds/explosion.wav");
    sound2.setBuffer(player_destroyed);
    sound2.setVolume(10.f);
    powerup.loadFromFile("sounds/powerup.ogg");
    sound3.setBuffer(powerup);
    sound3.setVolume(50.f);
}

void GameBoard::toggleEnemy(int x, int y)
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return;
    if(state==FINISHED_LOSS)
        return;
    else
    {
        board[y][x].hasEnemy=true;
    }
}

void GameBoard::removeEnemy(int x, int y)
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return;
    if(board[y][x].hasEnemy==false)
        return;
    else
        {
            board[y][x].hasEnemy=false;
        }
}

void GameBoard::togglePlayer(int x, int y)
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return;
    if(board[y][x].hasPlayer==1)
        return;
    else
        board[y][x].hasPlayer=true;
}

void GameBoard::removePlayer(int x, int y)
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return;
    if(board[y][x].hasPlayer==0)
        return;
    else
        board[y][x].hasPlayer=false;
}

void GameBoard::toggleBullet(int x, int y)
{
    if(state==FINISHED_LOSS)
        return;
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
    {
        if(mode==DEBUG)
        std::cout<<"Blad zakresu"<<std::endl;
        return;
    }
    if(board[y][x].hasBullet==true)
    {
        if(mode==DEBUG)
        std::cout<<"Bomba juz istnieje"<<std::endl;
        return;
    }
    else
        {
        board[y][x].hasBullet=true;
        }
}

void GameBoard::removeBullet(int x, int y)
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return;
    if(board[y][x].hasBullet==false)
        return;
    else
        board[y][x].hasBullet=false;
}

GameState GameBoard::getGameState()
{
    return state;
}

GameMode GameBoard::getGameMode()
{
    return mode;
}

char GameBoard::getFieldInfo(int x, int y)
{
    char info;
    if (hasEnemy(x,y)==1)
    {
        info='E';
        return info;
    }
    if (hasBullet(x,y)==1)
    {
        info='|';
        return info;
    }
    if (hasPlayer(x,y)==1)
    {
        info='X';
        return info;
    }
    if (hasEnemy(x,y)==0 and hasBullet(x,y)==0 and hasPlayer(x,y)==0)
    {
        info='_';
        return info;
    }
    if (hasBullet(x,y)==1 and hasEnemy(x,y)==1)
    {
        info='B';
        return info;
    }
}

void GameBoard::debug_display()
{
    std::string display;
    for (int idx_y = 0; idx_y<boardHeight; idx_y++)
    {
        for (int idx_x = 0; idx_x<boardWidth; idx_x++) {
            display+="[";
            if (hasEnemy(idx_x,idx_y)==1)
                display+="E";
            else
                display+=".";
            if (hasPlayer(idx_x,idx_y)==1)
                display+="X";
            else
                display+=".";
            if (hasBullet(idx_x,idx_y)==1)
                display+="I";
            else
                display+=".";
            display+="] ";

        } display+= "\n";
    }
    std::cout << display << std::endl;
}

void GameBoard::moveEnemy()
{
    if(state==FINISHED_LOSS)
        return;
    for (int idx_y = boardHeight; idx_y>=0; idx_y--)
    {
        for (int idx_x = boardWidth-1; idx_x>=0; idx_x--)
            {
                if(hasEnemy(idx_x,idx_y)==1)
                {
                    toggleEnemy(idx_x,idx_y+1);
                    removeEnemy(idx_x,idx_y);
                    isHitted(idx_x,idx_y+1);
                }
            }
    }
}

void GameBoard::moveBullet()
{
    if(state==FINISHED_LOSS)
        return;
    for (int idx_y = 0; idx_y<boardHeight; idx_y++)
        {
        for (int idx_x = 0; idx_x<boardWidth; idx_x++)
            {
                if(hasBullet(idx_x,idx_y)==1)
                {
                    toggleBullet(idx_x,idx_y-1);
                    removeBullet(idx_x,idx_y);
                    isHitted(idx_x,idx_y-1);
                }
            }
        }
}

void GameBoard::deployEnemy()
{
    if(state==FINISHED_LOSS)
        return;
    srand( time( NULL ) );
    for(int check=1; check<2; check++)
    {
        int rand_x = (rand() % boardWidth)+ 0;
        int rand_y = 0;
        if(board[rand_y][rand_x].hasEnemy==0)
        {
            if(mode==DEBUG)
            std::cout<<"Enemy Deployed"<<std::endl;
            board[rand_y][rand_x].hasEnemy=1;
        }
        else
            {
                if(mode==DEBUG)
                std::cout<<"Enemy Not Deployed"<<std::endl;
                check--;
            }
    }

}

void GameBoard::setPowerUp()
{
    if(state==FINISHED_LOSS)
        return;
    if(playerPowerUpState==1 or playerPowerUpState==2)
        return;
    srand( time( NULL ) );
    for(int check=1; check<2; check++)
    {
        int rand_x = (rand() % boardWidth)+ 0;
        int rand_y = 0;
        int randPoweUp = (rand() % 2)+ 0;
        if(board[rand_y][rand_x].hasEnemy==0)
        {
            if(mode==DEBUG)
                std::cout<<"PowerUp Deployed"<<std::endl;
            if(randPoweUp==0)
                board[rand_y][rand_x].powerUp1=true;
            if(randPoweUp==1)
                board[rand_y][rand_x].powerUp2=true;
        }
        else
            {
                if(mode==DEBUG)
                std::cout<<"Power Up Not Deployed"<<std::endl;
                check--;
            }
    }
}

void GameBoard::removePowerUp(int x, int y)
{
    if(x<0 or x>=boardWidth or y<0 or y>=boardHeight)
        return;
    if(board[y][x].powerUp1==true or board[y][x].powerUp2==true)
        {
            board[y][x].powerUp1=false;
            board[y][x].powerUp2=false;
        }
}

int GameBoard::hasPowerUp(int x, int y)
{
    if(board[y][x].powerUp1==false and board[y][x].powerUp2==false)
        return 0;
    if(board[y][x].powerUp1==true)
        return 1;
    if(board[y][x].powerUp2==true)
        return 2;
}

void GameBoard::setPowerUp(int x, int y, int type)
{
    int ptype = type;
    if(type == 1)
    {
       board[y][x].powerUp1=true;
    }
    if(type == 2)
    {
       board[y][x].powerUp2=true;
    }
}

void GameBoard::movePoweUp()
{
    if(state==FINISHED_LOSS)
        return;
    for (int idx_y = boardHeight; idx_y>=0; idx_y--)
    {
        for (int idx_x = boardWidth-1; idx_x>=0; idx_x--)
            {
                if(hasPowerUp(idx_x,idx_y)==1 or hasPowerUp(idx_x,idx_y)==2)
                {
                    setPowerUp(idx_x,idx_y+1,hasPowerUp(idx_x,idx_y));
                    removePowerUp(idx_x,idx_y);
                    isHitted(idx_x,idx_y+1);
                }
            }
        }
}

void GameBoard::destroyAllEnemies()
{
    if(state==FINISHED_LOSS)
        return;
    for (int idx_y = 0; idx_y < boardHeight-1; idx_y++) {
        for (int idx_x = 0; idx_x < boardWidth; idx_x++) {
                if(board[idx_y][idx_x].hasEnemy==1)
                {
                    setField(idx_x, idx_y, false, false, false, false, false);
                    score+=10;
                }
            }
        }
}

int GameBoard::getLivesNumber()
{
    return lives;
}

double GameBoard::getScore()
{
    return score;
}
