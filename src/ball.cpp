#include "ball.hpp"
#include <SFML/System/Time.hpp>
#include <iostream>

Ball::Ball()
{
    setRadius(radius);
    setOrigin(radius / 2, radius / 2);
    // assuming win dim is 1366x768!!!
    setPosition(1366.0 / 2, 768.0 / 2);
}

double Ball::getX() { return getPosition().x; }

double Ball::getY() { return getPosition().y; }

double Ball::getXVel() { return x_vel; }

double Ball::getYVel() { return y_vel; }

double Ball::getMaxYVel() { return max_y_vel; }

double Ball::getRadius() { return radius; }

bool Ball::getGoal() { return goal; }

double Ball::getAcc() { return acc; }

void Ball::setXVel(double vel) { x_vel = vel; }

void Ball::setYVel(double vel) { y_vel = vel; }

// resets ball's pos back to middle. gives random starting vel to ball
void Ball::resetBall()
{
    goal = false;
    setPosition(1366.0 / 2, 768.0 / 2);

    // List of possible starting vel to start from
    std::vector<int> Xvel_list{3, -3};
    std::vector<int> Yvel_list{0, 4, 3, 2, -2, -3, -4};

    int Xindex = rand() % Xvel_list.size(); // picks a random index
    int Yindex = rand() % Yvel_list.size(); // picks a random index
    setXVel(Xvel_list[Xindex]);
    setYVel(Yvel_list[Yindex]);
}

// checks for collision with left right border, up down border
void Ball::collisionCheck()
{
    double nextXPos = getX() + x_vel;
    double nextYPos = getY() + y_vel;
    // Left right border Collision
    if (nextXPos < radius || nextXPos > 1366 - radius)
    {
        // score check
        goal = true;
    }
    // Up down border collision
    else if (nextYPos <= radius || nextYPos >= 768 - radius)
    {
        setYVel(-y_vel);
    }
}

// moves ball accord to vel values and collisions
void Ball::moveBall() { move(x_vel, y_vel); }
