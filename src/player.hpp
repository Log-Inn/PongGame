#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <tuple>

class Player : public sf::RectangleShape
{
private:
public:
    Player();
    double width = 10;
    double height = 70;
    double vel = 0;
    double acc = 0;
    double maxVel = 5;
    char side{};
    sf::Keyboard::Key ascend;
    sf::Keyboard::Key descend;
    // char side;
    void create(char side);
    void updatePlayer(sf::Event &event);
    void movePlayer();
    // creates the rectangle/player. side is either 'L' or 'R'
    // void create() { if (side == 'L') }
};

// Player p1;
// p1.create('L') == sf::RectangleShape p1(sf::Vector2f(10,70));

#endif // PLAYER_HPP
