#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>

class Player : public sf::RectangleShape
{
private:
    double width = 10;
    double height = 70;
    double vel = 0;
    double maxVel = 5;

public:
    Player();
    sf::Keyboard::Key ascend;
    sf::Keyboard::Key descend;

    double getWidth();
    double getHeight();
    double getVelocity();
    double getMaxVel();
    char _side;

    void setVelocity(double velocity);
    void setMaxVel(double max_vel);

    void create(char side);
    void updatePlayer(sf::Event &event);
    void movePlayer();
};

#endif // PLAYER_HPP
