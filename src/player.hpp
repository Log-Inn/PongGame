#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Player : public sf::RectangleShape
{
public:
    enum ControlScheme
    {
        WASD,
        ARROW,
        CPU
    };

private:
    double width = 15;
    double height = 80;
    double vel = 0;
    double maxVel = 4;
    char _side;

public:
    Player();
    sf::Keyboard::Key ascend;
    sf::Keyboard::Key descend;

    double getWidth();
    double getHeight();
    double getVelocity();
    double getMaxVel();

    void setVelocity(double velocity);
    void setMaxVel(double max_vel);

    void create(char side, ControlScheme scheme);
    char getSide() const;
    void updatePlayer(sf::Event &event);
    void movePlayer();
};

#endif // PLAYER_HPP