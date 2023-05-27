#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Player : public sf::RectangleShape
{
public:
    enum MovementEvent
    {
        ASCEND_PRESSED = 1,
        DESCEND_PRESSED = 2,
        ASCEND_RELEASED = 3,
        ASCEND_RELEASED_DESCEND_PRESSED = 4,
        DESCEND_RELEASED = 5,
        DESCEND_RELEASED_ASCEND_PRESSED = 6,
        NAME = 0 // Not A Move Event
    };
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
    double maxVel = 480;
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

    Player::MovementEvent getPlayerMovementEvent(sf::Event &event);
    void updatePlayer(sf::Event &event);
    void updatePlayer(MovementEvent mv_event);
    void movePlayer(const float &dt);
};

#endif // PLAYER_HPP
