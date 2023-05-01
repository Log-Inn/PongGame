#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <tuple>

class Player : public sf::RectangleShape
{
private:
public:
    int width = 10;
    int height = 70;
    char side = side;
    Player();
    void create(char side);
    double vel = 0;
    double acc = 0;
    void movePlayer();

    // creates the rectangle/player. side is either 'L' or 'R'
    // void create() { if (side == 'L') }
};

// Player p1;
// p1.create('L') == sf::RectangleShape p1(sf::Vector2f(10,70));

#endif // PLAYER_HPP
