#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "GameLogic.h"

/*
This is the player class.
*/

class Player : public GameLogic
{
    //This is where all the function are stored.
public:
    Player(sf::Texture &texture,sf::Sprite &sprite):Texture_(texture),Sprite_(sprite)
    {}

    //This function reads the keyboard and sets the Desired Direction depending on the keyboard input.
    void ChangeDir()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            DDir_ = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            DDir_ = 270;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            DDir_ = 180;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            DDir_ =90;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            DDir_ = 45;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            DDir_ = 315;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            DDir_ = 135;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            DDir_ = 225;
        }
    }

    //This function draws crops the sprite sheet using CDir and sets the players sprite.
    void DrawPlayer()
    {
        double Mover{16};
        Mover = ( CDir_ / 45 ) * 16;
        Texture_.loadFromFile("test.png", sf::IntRect(Mover,0,16,16));
        Sprite_.setTexture(Texture_);
    }

    //This function deccelerates the player. Only use this when buttons are pushed!
    void SetDecceleration()
    {
        if(PlayerXSpeed_ < 0)
        {
            PlayerXSpeed_ += PlayerDccSpeed_;
        }
        else if(PlayerXSpeed_ > 0)
        {
            PlayerXSpeed_ -= PlayerDccSpeed_;
        }
        if(PlayerYSpeed_ < 0)
        {
            PlayerYSpeed_ += PlayerDccSpeed_;
        }
        else if(PlayerYSpeed_ > 0)
        {
            PlayerYSpeed_ -= PlayerDccSpeed_;
        }
        if(std::abs(0-PlayerXSpeed_) <= PlayerDccSpeed_)
        {
            PlayerXSpeed_ = 0;
        }
        if(std::abs(0-PlayerYSpeed_) <= PlayerDccSpeed_)
        {
            PlayerYSpeed_ = 0;
        }
    }

    //This function accelerates the player. Only use this when no buttons are pushed!
    void SetAcceleration()
    {
        if(PlayerXSpeed_ < GetXYSpeed(DDir_,PlayerSpeed_).first)
        {
            PlayerXSpeed_ += PlayerAccSpeed_;
        }
        if(PlayerXSpeed_ > GetXYSpeed(DDir_,PlayerSpeed_).first)
        {
            PlayerXSpeed_ -= PlayerAccSpeed_;
        }
        if(PlayerYSpeed_ < GetXYSpeed(DDir_,PlayerSpeed_).second)
        {
            PlayerYSpeed_ += PlayerAccSpeed_;
        }
        if(PlayerYSpeed_ > GetXYSpeed(DDir_,PlayerSpeed_).second)
        {
            PlayerYSpeed_ -= PlayerAccSpeed_;
        }
        if(std::abs(GetXYSpeed(DDir_,PlayerSpeed_).first-PlayerXSpeed_) <= PlayerAccSpeed_)
        {
            PlayerXSpeed_ = GetXYSpeed(DDir_,PlayerSpeed_).first;
        }
        if(std::abs(GetXYSpeed(DDir_,PlayerSpeed_).second-PlayerYSpeed_) <= PlayerAccSpeed_)
        {
            PlayerYSpeed_ = GetXYSpeed(DDir_,PlayerSpeed_).second;
        }
    }

    //This function turns the player towards the Desired Direction.
    double GetCDir()
    {
        double TempDDir{DDir_};
        double TempCDir{CDir_};

        if((TempDDir == 0 and CDir_ > 180) or (TempDDir == 45 and CDir_ > 180) or (TempDDir == 90 and CDir_ > 270))
        {
            TempDDir = 360;
        }
        if(TempCDir == 0 and TempDDir > 180 and TempDDir < 360)
        {
            CDir_ = 360 - 45;
            return CDir_;
        }
        if(TempCDir == 45 and TempDDir > 225 and TempDDir < 360)
        {
            CDir_ -=45;
            return CDir_;
        }
        if(TempCDir == 90 and TempDDir == 315)
        {
            CDir_ = 360 - 45;
            return CDir_;
        }
        if(std::abs(TempCDir - TempDDir) == 180)
        {
            CDir_ += 45;
        }
        else if((TempCDir - TempDDir) > 0)
        {
            CDir_ -= 45;
        }
        else if ((TempCDir - TempDDir) < 0)
        {
            CDir_ += 45;
        }
        if(CDir_ == 360)
        {
            CDir_ = 0;
        }
        return CDir_;
    }

    //Below are various Get and Set functions, no further explanation needed.
    void SetPlayerXPos(double ny)
    {
        PlayerXPos_+=ny;
    }
    void SetPlayerYPos(double ny)
    {
        PlayerYPos_+=ny;
    }
    double GetPlayerXSpeed()
    {
        return PlayerXSpeed_;
    }
    double GetPlayerYSpeed()
    {
        return PlayerYSpeed_;
    }
    void SetPosition()
    {
        Sprite_.setPosition(PlayerXPos_,PlayerYPos_);
    }
    sf::Sprite GetSprite()
    {
        return Sprite_;
    }
    void SetCDir(double ny)
    {
        CDir_ = ny;
    }
    double SpritePos()
    {
        return Sprite_.getPosition().x;
    }
    double GetXPos()
    {
        return PlayerXPos_;
    }
    double GetYPos()
    {
        return PlayerYPos_;
    }

    //This is where all the variables are stored.
    //Const variables should only be changed here and not by any function.
private:

    std::pair <double,double> XYSpeed_ {0,0};
    sf::Texture Texture_;
    sf::Sprite Sprite_;
    double CDir_{0}; //This is the current direction the player is facing(0 - 360°).
    double DDir_{0}; //This is the direction the player is turning towards(0 - 360°).

    double PlayerXPos_{0}; //This is the players current X position on the screen(0 - ScreenWidth)
    double PlayerYPos_{0};  //This is the players current Y position on the screen(0 - ScreenHight)

    double PlayerXSpeed_{0}; //This is the players current X speed (< 0 is left) (> 0 is right)
    double PlayerYSpeed_{0}; //This is the players current Y speed (< 0 is up) (> 0 is down)

    double const PlayerAccSpeed_{0.005}; //This controls how fast the player accelerates.
    double const PlayerDccSpeed_{0.001}; //This controls how fast the player decelerates.
    double const PlayerSpeed_{0.7}; //This is the highest speed the player can travel.
};

#endif // PLAYER_H_INCLUDED
