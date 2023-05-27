#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>


class Ball : public sf::CircleShape
{
private:
    double x = getPosition().x;
    double y = getPosition().y;
    double x_vel = 0;
    double y_vel = 0;
    double max_y_vel = 600;
    double radius = 8;

    // acc is how much the vel increases every collision with a paddle
    double acc = 30;

    // goal is a bool of whether a goal was scored
    bool goal = true;

public:
    Ball();

    double getX();
    double getY();

    double getXVel();
    double getYVel();
    double getMaxYVel();

    double getRadius();
    double getAcc();
    bool getGoal();

    void setXVel(double vel);
    void setYVel(double vel);

    void collisionCheck(const float &dt);
    void resetBall();
    void moveBall(const float &dt);
};

#endif // BALL_HPP
