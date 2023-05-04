#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>


class Ball : public sf::CircleShape
{
private:
    double x = this->getPosition().x;
    double y = this->getPosition().y;
    double x_vel = 0;
    double y_vel = 0;
    double radius = 8;
    bool goal = true;

    void collisionCheck();

public:
    Ball();

    double getX();
    double getY();

    double getXVel();
    double getYVel();
    double getRadius();

    void setXVel(double vel);
    void setYVel(double vel);

    bool goalScored();
    void resetBall();
    void moveBall();
};

#endif // BALL_HPP
