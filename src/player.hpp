#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player : public sf::RectangleShape
{
private:
public:
    Player();
    void create(char side);
    double vel = 0;
    double acc = 0;
    void moveUp();
    void moveDown();
    // creates the rectangle/player. side is either 'L' or 'R'
    // void create() { if (side == 'L') }
};

// Player p1;
// p1.create('L') == sf::RectangleShape p1(sf::Vector2f(10,70));

#endif // PLAYER_HPP
