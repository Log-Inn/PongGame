#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player()
{
    this->setSize(sf::Vector2f(width, height));
    this->setOrigin(width / 2, height / 2);
}

void Player::create(char side)
{
    if (side == 'L')
    {
        this->setPosition(25, 300);
        ascend = sf::Keyboard::W;
        descend = sf::Keyboard::S;
    }
    else if (side == 'R')
    {
        this->setPosition(1025, 300);
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
            this->acc = -0.2;
            // if (this->vel > 0)
            // {
            //     this->vel = 0;
            // }
        }
        else if (event.key.code == descend)
        {
            this->acc = 0.2;
            // if (this->vel < 0)
            // {
            //     this->vel = 0;
            // }
        }
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == ascend)
        {
            // this->acc = 0;
            this->vel = 0;
            if (!sf::Keyboard::isKeyPressed(descend))
            {
                this->acc = 0;
            }
        }
        else if (event.key.code == descend)
        {
            // this->acc = 0;
            this->vel = 0;
            if (!sf::Keyboard::isKeyPressed(ascend))
            {
                this->acc = 0;
            }
        }
    }
}

void Player::movePlayer()
{
    if ((this->vel < this->maxVel) && (this->vel > -this->maxVel))
    {
        this->vel += this->acc;
    }

    double nextPos = this->getPosition().y + this->vel;

    if (nextPos <= this->height / 2 || nextPos >= 768 - this->height / 2)
    {
        this->vel = 0;
    }

    this->move(0, vel);
}
