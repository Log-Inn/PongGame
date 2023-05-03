#include "ball.hpp"
#include <SFML/System/Time.hpp>
#include <iostream>

Ball::Ball()
{
    this->setRadius(this->radius);
    this->setOrigin(this->radius / 2, this->radius / 2);
    this->setPosition(1366.0 / 2, 768.0 / 2);
}

double Ball::getX() { return this->getPosition().x; }

double Ball::getY() { return this->getPosition().y; }

void Ball::setXVel(double vel) { this->x_vel = vel; }

void Ball::setYVel(double vel) { this->y_vel = vel; }

void Ball::resetBall()
{
    // score check
    this->setPosition(1366.0 / 2, 768.0 / 2);

    // List of possible starting vel to start from
    std::vector<int> Xvel_list{4, 3, 2, -2, -3, -4};
    std::vector<int> Yvel_list{0, 4, 3, 2, -2, -3, -4};
    int Xindex = rand() % Xvel_list.size();
    int Yindex = rand() % Yvel_list.size(); // pick a random index
    this->setXVel(Xvel_list[Xindex]);
    this->setYVel(Yvel_list[Yindex]);
}

void Ball::collisionCheck()
{
    double nextXPos = this->getX() + this->x_vel;
    double nextYPos = this->getY() + this->y_vel;
    // Border Collision
    if (nextXPos < this->radius || nextXPos > 1366 - this->radius)
    {
        // score check
        this->resetBall();
    }
    else if (nextYPos <= this->radius || nextYPos >= 768 - this->radius)
    {
        this->setYVel(-y_vel);
    }
}

void Ball::moveBall()
{
    this->collisionCheck();
    this->move(x_vel, y_vel);
}

int Ball::goalScored() {
    
}
