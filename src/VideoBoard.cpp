#include "VideoBoard.h"
#include "GameBoard.h"
#include <iostream>

VideoBoard::VideoBoard(GameBoard&Aliens, int x0, int y0, int fx, int fy):board(Aliens)
{
    board_width=board.getBoardWidth();
    board_height=board.getBoardHeight();
    field_lenght=fx;
    field_y=fy;
    VideoBoard::x0=x0;
    VideoBoard::y0=y0;
}

void VideoBoard::loadTextures()
{
    if(board.getGameMode()==EASY)
        enemyDeployTime=4;
    if(board.getGameMode()==HARD)
        enemyDeployTime=3;

    font.loadFromFile("image/pixelated.ttf");
    heart.loadFromFile("image/heart.png");
    alien1.loadFromFile("image/alien1.png");
    alien2.loadFromFile("image/alien2.png");
    powerup.loadFromFile("image/powerup.png");
    powerup1.loadFromFile("image/bomb1.png");
    powerup2.loadFromFile("image/slow1.png");
    fire.loadFromFile("image/fire.png");
    player.loadFromFile("image/player.png");
    laser.loadFromFile("image/lasser.png");
    back_ground.loadFromFile("image/background1_1.png");
    endgame.loadFromFile("image/endgamescreen.png");
    fire_sound.loadFromFile("sounds/shoot.wav");

}

void VideoBoard::play(sf::RenderWindow &window)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                {

                if (event.key.code == sf::Keyboard::D)
                    {
                        board.movePlayer(1);

                    }
                if (event.key.code == sf::Keyboard::A)
                    {
                        board.movePlayer(2);

                    }
                if (event.key.code == sf::Keyboard::Space)
                    {
                        if(board.getGameMode()==DEBUG)
                        std::cout<<"Bomb deployed"<<std::endl;
                        board.toggleBullet(board.playerXPOS(),board.getBoardHeight()-2);
                        sound.setBuffer(fire_sound);
                        sound.setVolume(5.f);
                        sound.play();
                    }
                if (event.key.code == sf::Keyboard::N)
                    {
                        if(board.playerPowerUpState==1)
                        {
                            if(board.getGameMode()==DEBUG)
                                std::cout<<"PowerUp1 activated"<<std::endl;
                            board.destroyAllEnemies();
                            board.playerPowerUpState=0;
                        }
                    }
                if (event.key.code == sf::Keyboard::M)
                    {
                        if(board.playerPowerUpState==2)
                        {
                            if(board.getGameMode()==DEBUG)
                                std::cout<<"PowerUp2"<<std::endl;
                            slowTimeCount=1;
                        }
                    }
                }
            if(board.getGameState()==RUNNING)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (event.mouseButton.x >= 553 and event.mouseButton.x <= 920 and event.mouseButton.y >= 727 and event.mouseButton.y <= 814)
                        {
                            board.setBoard();
                            board.score=0;
                            board.playerPowerUpState=0;
                            board.lives=3;
                            if(board.getGameMode()==EASY)
                            enemyDeployTime=4;
                            if(board.getGameMode()==HARD)
                            enemyDeployTime=3;
                        }
                        if (event.mouseButton.x >= 553 and event.mouseButton.x <= 920 and event.mouseButton.y >= 865 and event.mouseButton.y <= 952)
                        {
                            event.type = sf::Event::Closed;
                        }
                    }
                }
            }

            if(board.getGameState()==FINISHED_LOSS)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (event.mouseButton.x >= 120 and event.mouseButton.x <= 487 and event.mouseButton.y >= 856 and event.mouseButton.y <= 943)
                        {
                            board.state=RUNNING;
                            board.setBoard();
                            board.score=0;
                            board.playerPowerUpState=0;
                            board.lives=3;
                            if(board.getGameMode()==EASY)
                            enemyDeployTime=4;
                            if(board.getGameMode()==HARD)
                            enemyDeployTime=3;
                        }
                        if (event.mouseButton.x >= 538 and event.mouseButton.x <= 905 and event.mouseButton.y >= 856 and event.mouseButton.y <= 943)
                        {
                            event.type = sf::Event::Closed;
                        }
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


        draw_board(window);
        window.display();
        sf::Clock Clock;
        sf::Time elapsed;
        std::cout<<enemyDeployTime<<std::endl;
        double time;
        int mainTimer=0;

        while(mainTimer==0)
            {
                elapsed=Clock.getElapsedTime();
                time=elapsed.asSeconds();
                time=time/1;
                if(time>0.1)
                    {
                        board.moveBullet();
                        board.movePoweUp();
                        enemyTimer++;
                        mainTimer++;
                        powerUpTimer++;
                        if(slowTimeCount==1)
                            {
                            slowTimeTime++;
                            enemyDeployTime=20;
                            }
                    }
                    if(enemyTimer>=enemyDeployTime)
                    {
                        board.moveEnemy();
                        board.deployEnemy();


                        enemyTimer=0;
                    }
                    if(slowTimeTime>=50)
                    {
                        if(board.getGameMode()==EASY)
                            enemyDeployTime=4;
                        if(board.getGameMode()==HARD)
                            enemyDeployTime=3;
                        board.playerPowerUpState=0;
                        slowTimeCount=0;
                        slowTimeTime=0;
                    }
                    if(powerUpTimer>=200)
                    {
                        board.movePoweUp();
                        board.setPowerUp();
                        powerUpTimer=0;
                        mainTimer=0;
                    }
            }
        }



}



void VideoBoard::draw_board(sf::RenderWindow &window)
{
    for (int idx_y = 0; idx_y<board_height; idx_y++)
    {
        for (int idx_x = 0; idx_x<board_width; idx_x++)
        {

            for(int i=0; i<board.getLivesNumber();i++)
                VdrawLivesNumber(window,630,120,i);

            if(board.hasEnemy(idx_x,idx_y)==1)
            {
                VsetEnemy(window,idx_x,idx_y);
            }
            if(board.hasPlayer(idx_x,idx_y)==1)
            {
                VsetPlayer(window,idx_x,idx_y);
            }
            if(board.hasBullet(idx_x,idx_y)==1)
            {
                VsetBullet(window,idx_x,idx_y);
            }
            if(board.hasPowerUp(idx_x,idx_y)==1)
            {
                VsetPU1(window,idx_x,idx_y);
            }
            if(board.hasPowerUp(idx_x,idx_y)==2)
            {
                VsetPU2(window,idx_x,idx_y);
            }
            if(board.hasBullet(idx_x,idx_y)==1 and board.hasEnemy(idx_x,idx_y)==1)
            {
                VsetBoom(window,idx_x,idx_y);

            }
        }
    }
    VdrawScore(window,690,600);
    if(board.playerPowerUpState==1)
             VdrawPowerUp(window,1);
    if(board.playerPowerUpState==2)
             VdrawPowerUp(window,2);
    if(board.getGameState()==FINISHED_LOSS)
            EndGameScreen(window);
}

void VideoBoard::VsetEnemy(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole.setPointCount(4);
    //pole.setFillColor(sf::Color(100,200,150));
    pole.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_y));
    pole.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_y));
    pole.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_y+idx_y*field_y-1));
    pole.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_y+idx_y*field_y-1));
 //   int randAlien = (rand() % 2)+ 0;
 //   if(randAlien==0)
   //     pole.setTexture(&alien1);
  //  if(randAlien==1)
        pole.setTexture(&alien2);
    window.draw(pole);
}

void VideoBoard::VsetPlayer(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole.setPointCount(4);
    pole.setFillColor(sf::Color(229, 229, 229));
    pole.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_y));
    pole.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_y));
    pole.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_y+idx_y*field_y-1));
    pole.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_y+idx_y*field_y-1));
    pole.setTexture(&player);
    window.draw(pole);
}

void VideoBoard::VsetBullet(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole.setPointCount(4);
    //pole.setFillColor(sf::Color(40,250,50));
    pole.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_y));
    pole.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_y));
    pole.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_y+idx_y*field_y-1));
    pole.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_y+idx_y*field_y-1));
    pole.setTexture(&laser);
    window.draw(pole);
}

void VideoBoard::VsetBoom(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole.setPointCount(4);
    pole.setFillColor(sf::Color(229, 229, 229));
    pole.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_y));
    pole.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_y));
    pole.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_y+idx_y*field_y-1));
    pole.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_y+idx_y*field_y-1));
    //pole.setTexture(&player);
    window.draw(pole);
}

void VideoBoard::VsetPU1(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole2.setPointCount(4);
    //pole.setFillColor(sf::Color(40,50,250));
    pole2.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_y));
    pole2.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_y));
    pole2.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_y+idx_y*field_y-1));
    pole2.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_y+idx_y*field_y-1));
    pole2.setTexture(&powerup);
    window.draw(pole2);
}

void VideoBoard::VsetPU2(sf::RenderWindow &window, int idx_x, int idx_y)
{
    pole2.setPointCount(4);
   //pole.setFillColor(sf::Color(240,50,50));
    pole2.setPoint(0, sf::Vector2f(x0+idx_x*field_lenght,y0+idx_y*field_y));
    pole2.setPoint(1, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+idx_y*field_y));
    pole2.setPoint(2, sf::Vector2f(x0+field_lenght+idx_x*field_lenght-1,y0+field_y+idx_y*field_y-1));
    pole2.setPoint(3, sf::Vector2f(x0+idx_x*field_lenght,y0+field_y+idx_y*field_y-1));
    pole2.setTexture(&powerup);
    window.draw(pole2);
}

void VideoBoard::VdrawLivesNumber(sf::RenderWindow &window, int x, int y, int i)
{
    pole1.setPointCount(4);
            pole1.setFillColor(sf::Color(240,50,50));
            pole1.setPoint(0, sf::Vector2f(x+70*i,y));
            pole1.setPoint(1, sf::Vector2f(x+70+70*i,y));
            pole1.setPoint(2, sf::Vector2f(x+70+70*i,y+70));
            pole1.setPoint(3, sf::Vector2f(x+70*i,y+70));
            pole1.setTexture(&heart);
    window.draw(pole1);
}

void VideoBoard::EndGameScreen(sf::RenderWindow &window)
{
    background.setPointCount(4);
    background.setPoint(0, sf::Vector2f(0,0));
    background.setPoint(1, sf::Vector2f(1000,0));
    background.setPoint(2, sf::Vector2f(1000,1000));
    background.setPoint(3, sf::Vector2f(0,1000));
    background.setTexture(&endgame);

    sf::Text score_text_end;
    int s=board.getScore();
    score_text_end.setString(std::to_string(s));
    score_text_end.setFont(font);
    score_text_end.setCharacterSize(100);
    score_text_end.setFillColor(sf::Color::White);
    score_text_end.setPosition(634,692);
    window.draw(background);
    window.draw(score_text_end);


}

void VideoBoard::VdrawPowerUp(sf::RenderWindow &window, int status)
{
    if(status==1)
    {
    powerups.setPointCount(4);
    powerups.setPoint(0, sf::Vector2f(623,367));
    powerups.setPoint(1, sf::Vector2f(723,367));
    powerups.setPoint(2, sf::Vector2f(723,467));
    powerups.setPoint(3, sf::Vector2f(623,467));
    powerups.setTexture(&powerup1);
    window.draw(powerups);
    }

    if(status==2)
    {
    powerups.setPointCount(4);
    powerups.setPoint(0, sf::Vector2f(749,367));
    powerups.setPoint(1, sf::Vector2f(849,367));
    powerups.setPoint(2, sf::Vector2f(849,467));
    powerups.setPoint(3, sf::Vector2f(749,467));
    powerups.setTexture(&powerup2);
    window.draw(powerups);
    }
}

void VideoBoard::VdrawScore(sf::RenderWindow &window, int x, int y)
{
    sf::Text score_text;
    int s=board.getScore();
    score_text.setString(std::to_string(s));
    score_text.setFont(font);
    score_text.setCharacterSize(48);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(x,y);
    window.draw(score_text);
}
