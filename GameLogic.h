#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

/*
This is the GameLogic class.
It contains useful functions used all around the game.
*/

// Test för att se hur bra github är.


class GameLogic
{
    public:

    //This function takes a Speed and Degree and returns a X, Y value.
    std::pair <double,double> GetXYSpeed(double Dir, double BulletSpeed)
    {
        std::pair <double,double> test;
        test.first = BulletSpeed * std::cos(Dir * 3.14159265359 / 180);
        test.second = -(BulletSpeed * std::sin(Dir * 3.14159265359 / 180));
        return test;
    }

    std::string CollisionSide(sf::FloatRect Moving, sf::FloatRect Static)
    {
        if(Moving.top - Static.top <= -Moving.height)
        {
            return "Above";
        }
        else if(Moving.top - Static.top >= Static.height)
        {
            return "Below";
        }
        else if(Moving.left - Static.left <= -Moving.width)
        {
            return "Left";
        }
        else if(Moving.left - Static.left >= Static.width)
        {
            return "Right";
        }
    }
};

#endif // GAMELOGIC_H_INCLUDED
