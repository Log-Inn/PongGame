#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
# include "../pong.hpp"


class Player : public sf::RectangleShape
{
private:
    double width = 15; // 10
    double height = 80; // 70
    //double vel = 0;
    double maxVel = 4; // 5
    int _score = 0;
    char _side {};

public:
    Player();
    sf::Keyboard::Key ascend;
    sf::Keyboard::Key descend;

    void hookWindow(Pong* pg);
    Pong* hook;

    double getWidth();
    double getHeight();
    double getVelocity();
    double getMaxVel();
    int    getScore();
    char   getSide();

    double vel = 0;

    void setVelocity(double vel);
    void setMaxVel(double max_vel);

    void create(char side);
    void updatePlayer(sf::Event &event);
    virtual void movePlayer();
};

#endif // PLAYER_HPP
