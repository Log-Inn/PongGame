#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
# include "pong.hpp" 


class Player : public sf::RectangleShape
{
private:
    double width = 10;
    double height = 70;
    double vel = 0;
    double maxVel = 5;
    Pong* hook;

public:
    Player();
    sf::Keyboard::Key ascend;
    sf::Keyboard::Key descend;

    void hookWindow(Pong* pg);

    double getWidth();
    double getHeight();
    double getVelocity();
    double getMaxVel();
    char _side;

    void setVelocity(double vel);
    void setMaxVel(double max_vel);

    void create(char side);
    virtual void updatePlayer(sf::Event &event);
    virtual void movePlayer();
};

#endif // PLAYER_HPP
