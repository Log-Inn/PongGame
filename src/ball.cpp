#include "ball.hpp"
#include <SFML/System/Time.hpp>
#include <iostream>

Ball::Ball()
{
    this->setRadius(this->radius);
    this->setOrigin(this->radius / 2, this->radius / 2);
    // assuming win dim is 1366x768
    this->setPosition(1366.0 / 2, 768.0 / 2);
}

double Ball::getX() { return this->getPosition().x; } 

double Ball::getY() { return this->getPosition().y; }

double Ball::getXVel() { return x_vel; }

double Ball::getYVel() { return y_vel; }

double Ball::getRadius() { return radius; }

void Ball::setXVel(double vel) { this->x_vel = vel; }

void Ball::setYVel(double vel) { this->y_vel = vel; }

bool Ball::goalScored() { return goal; }

// resets ball's pos back to middle. gives random starting vel to ball
void Ball::resetBall()
{
    goal = false;
    // score check
    this->setPosition(1000.0 / 2, 768.0 / 2);

    // List of possible starting vel to start from
    std::vector<int> Xvel_list{3, -3};
    std::vector<int> Yvel_list{0, 4, 3, 2, -2, -3, -4};
    int Xindex = rand() % Xvel_list.size();
    int Yindex = rand() % Yvel_list.size(); // pick a random index
    this->setXVel(Xvel_list[Xindex]);
    this->setYVel(Yvel_list[Yindex]);
}

// checks for collision with left right border, up down border and paddles
void Ball::collisionCheck()
{
    double nextXPos = this->getX() + this->x_vel;
    double nextYPos = this->getY() + this->y_vel;
    // Left right border Collision
    if (nextXPos < this->radius || nextXPos > 1366 - this->radius)
    {
        // score check
        goal = true;
    }
    // Up down border collision
    else if (nextYPos <= this->radius || nextYPos >= 768 - this->radius)
    {
        this->setYVel(-y_vel);
    }
    // Paddle collision
}

// moves ball accord to vel values and collisions
void Ball::moveBall()
{
    this->collisionCheck();
    this->move(x_vel, y_vel);
}
