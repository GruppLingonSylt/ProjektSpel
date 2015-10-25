#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <utility>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "Player.h"
#include "Bullet.h"

//This is the main.
//while(Window.isOpen()) is the game loop.

/*
Please Read:

All new words in variable/function names should be capitalized, for example
void setwindowsize() = Not correct.
void SetWindowSize() = Correct!

double windowxsize = Not correct.
double WindowXSize = Correct!

////////////////////////////////////////////////////////////////////////////////

They should not look like this

if(x = 5){
std::cout << "This is bad!";
}

If sentences should look like this

if(x = 5)
{
    std::cout << "Like this!";
}

////////////////////////////////////////////////////////////////////////////////

Add spaces between every +,-,<,>,... sign

5+5 = Not correct.

5 + 5 = Correct!

////////////////////////////////////////////////////////////////////////////////

If you don't know how to write something ask or look at the existing code!
Please use comments often.
*/

bool NoKeys(sf::Keyboard::Key Left,sf::Keyboard::Key Right,sf::Keyboard::Key Up,sf::Keyboard::Key Down)
{
    //This function returns true when none of the passed in buttons are pressed.
    //It's used for deceleration and acceleration.
    if(!(sf::Keyboard::isKeyPressed(Left))
       and !(sf::Keyboard::isKeyPressed(Right))
       and !(sf::Keyboard::isKeyPressed(Up))
       and !(sf::Keyboard::isKeyPressed(Down)))
    {
        return true;
    }
    return false;
}

bool JSinglePress(bool &JPressed)
{
    //This function returns true sets JPressed to true every time you begin to press J.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && JPressed == false)
    {
        JPressed = true;
        return true;
    }
    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::J)))
    {
        JPressed = false;
        return false;
    }
    return false;
}

int main()
{
    sf::RenderWindow Window(sf::VideoMode(256,224),"SFMLtest");

    sf::Texture pTexture;
    sf::Texture bg;
    sf::Texture BlockTexture;

    bg.loadFromFile("map.png");
    BlockTexture.loadFromFile("Block.png");
    sf::Sprite sPlayer;
    sf::Sprite bg2;
    sf::Sprite temp;
    sf::Sprite BlockSprite;

    std::vector<Bullet> BulletVector;
    bool JPressed;

    int FrameCtr{0};
    int FrameRate{120};
    Window.setFramerateLimit(FrameRate);

    bg2.setTexture(bg);
    Player b(pTexture,sPlayer);
    Window.setFramerateLimit(120);
    while(Window.isOpen())
    {
        sf::Event Event;
        while(Window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
            {
                Window.close();
                std::cout << "Closed Window" << std::endl;
            }
        }

        b.ChangeDir();


        if((FrameCtr % 4) == 0)
        {
            b.SetCDir(b.GetCDir());
        }

        Window.draw(bg2);
        b.DrawPlayer();

        FrameCtr += 1;

        if(JSinglePress(JPressed))
        {
            Bullet bullet(b.GetCDir(),b.GetXPos(),b.GetYPos());
            BulletVector.push_back(bullet);
            std::cout << BulletVector.size() << std::endl;
        }

        for(int i{0};i < BulletVector.size();i++)
        {
            BulletVector.at(i).UppdateBulletPosition();
            BulletVector.at(i).DrawBullet(Window);
        }

        if(!NoKeys(sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D))
        {
            b.SetAcceleration();
            //std::cout << GetXYSpeed(DDir,PlayerSpeed).first << std::endl;
        }
        else
        {
            b.SetDecceleration();
        }

        b.SetPlayerXPos(b.GetPlayerXSpeed());
        b.SetPlayerYPos(b.GetPlayerYSpeed());
        b.SetPosition();

        Window.draw(b.GetSprite());
        Window.display();
        Window.clear();
    }


}
