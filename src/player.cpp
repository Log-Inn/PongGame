#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player()
{
    this->setSize(sf::Vector2f(width, height));
    this->setOrigin(width / 2, height / 2);
}
void Player::hookWindow(Pong* pg) {hook = pg; }

void Player::setXPos(Pong* pg) 
{width = pg->getWindowWidth(); 
}

void Player::setYPos(Pong* pg) {height = pg->getWindowHeight()/2; }

double Player::getWidth() { return width; }

double Player::getHeight() { return height; }

double Player::getVelocity() { return vel; }

double Player::getMaxVel() { return maxVel; }

void Player::setVelocity(double velocity) { this->vel = velocity; }

void Player::setMaxVel(double max_vel) { this->maxVel = max_vel; }

void Player::create(char side)
{
    this->_side = side;
    if (side == 'L')
    {
        this->setPosition(25, hook->getWindowHeight()/2);
        // this->setPosition(25, 384);
        ascend = sf::Keyboard::W;
        descend = sf::Keyboard::S;
    }
    else if (side == 'R')
    {
        this->setPosition(1000, 384);
        ascend = sf::Keyboard::Up;
        descend = sf::Keyboard::Down;
    }
}

void Player::updatePlayer(sf::Event &event)
{
    // std::cout << event.type << "\n";
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == ascend)
        {
            this->vel = -this->maxVel;
        }
        else if (event.key.code == descend)
        {
            this->vel = this->maxVel;
        }
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == ascend)
        {
            if (sf::Keyboard::isKeyPressed(descend))
            {
                this->vel = this->maxVel;
            }
            else
            {
                this->vel = 0;
            }
        }
        else if (event.key.code == descend)
        {
            if (sf::Keyboard::isKeyPressed(ascend))
            {
                this->vel = -this->maxVel;
            }
            else
            {
                this->vel = 0;
            }
        }
    }
}

void Player::movePlayer()
{
    double nextPos = this->getPosition().y + this->vel;

    if (nextPos <= this->height / 2 || nextPos >= 768 - this->height / 2)
    {
        this->vel = 0;
    }

    this->move(0, vel);
}
