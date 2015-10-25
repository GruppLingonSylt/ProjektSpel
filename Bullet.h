#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
//#include "GameLogic.h"

/*
This is the Bullet class.
*/

class Bullet : public GameLogic
{
    public:

        //This is the constructor for bullet, it takes the direction the player is facing and the players X,Y position
        Bullet(double Dir,double PlayerXPos,double PlayerYPos)
        {
            BulletTexture.loadFromFile("Bullet.png");
            BulletXPos = PlayerXPos +7;
            BulletYPos = PlayerYPos +7;

            BulletXSpeed = GetXYSpeed(Dir,BulletSpeed).first;
            BulletYSpeed = GetXYSpeed(Dir,BulletSpeed).second; //This sets the bullets speed depending on the players direction
        }

        //Get and Set the bullet position
        double GetBulletXPos()
        {
            return BulletXPos;
        }
        double GetBulletYPos()
        {
            return BulletYPos;
        }
        void SetBulletXPos(double Pos)
        {
            BulletXPos = Pos;
        }
        void SetBulletYPos(double Pos)
        {
            BulletYPos = Pos;
        }

        //Get and Set the bullet speed
        double GetBulletXSpeed()
        {
            return BulletXSpeed;
        }
        double GetBulletYSpeed()
        {
            return BulletYSpeed;
        }
        void SetBulletXSpeed(double Speed)
        {
            BulletXSpeed = Speed;
        }
        void SetBulletYSpeed(double Speed)
        {
            BulletYSpeed = Speed;
        }

        void DrawBullet(sf::RenderWindow& Window)
        {
            BulletSprite.setTexture(BulletTexture);
            BulletSprite.setPosition(BulletXPos,BulletYPos);
            Window.draw(BulletSprite);
        }

        void UppdateBulletPosition()
        {
            BulletXPos += BulletXSpeed;
            BulletYPos += BulletYSpeed;
        }

        sf::Sprite GetBulletSprite()
        {
            return BulletSprite;
        }

    private:
        sf::Texture BulletTexture;
        sf::Sprite BulletSprite;

        double BulletXPos{0}; //The bullets current X position.
        double BulletYPos{0}; //The bullets current Y position.

        double BulletXSpeed{0}; //The bullets current X speed.
        double BulletYSpeed{0}; //The bullets current Y speed.

        double BulletSpeed{2}; //The vector speed at witch the bullet should travel.

};

#endif // BULLET_H_INCLUDED
