#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player()
{
    setSize(sf::Vector2f(width, height));
    setOrigin(width / 2, height / 2);
}

double Player::getWidth() { return width; }

double Player::getHeight() { return height; }

double Player::getVelocity() { return vel; }

double Player::getMaxVel() { return maxVel; }

void Player::setVelocity(double velocity) { vel = velocity; }

void Player::setMaxVel(double max_vel) { maxVel = max_vel; }

// creates Left or Right player based on "side"
void Player::create(char side)
{
    if (side == 'L')
    {
        setPosition(50, 384);
        ascend = sf::Keyboard::W;
        descend = sf::Keyboard::S;
    }
    else if (side == 'R')
    {
        setPosition(1316, 384);
        ascend = sf::Keyboard::Up;
        descend = sf::Keyboard::Down;
    }
}

//checks for input from player to go up or down or stop
void Player::updatePlayer(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == ascend)
        {
            vel = -maxVel;
        }
        else if (event.key.code == descend)
        {
            vel = maxVel;
        }
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == ascend)
        {
            if (sf::Keyboard::isKeyPressed(descend))
            {
                vel = maxVel;
            }
            else
            {
                vel = 0;
            }
        }
        else if (event.key.code == descend)
        {
            if (sf::Keyboard::isKeyPressed(ascend))
            {
                vel = -maxVel;
            }
            else
            {
                vel = 0;
            }
        }
    }
}

void Player::movePlayer()
{
    double nextPos = getPosition().y + vel;

    if (nextPos <= height / 2 || nextPos >= 768 - height / 2)
    {
        vel = 0;
    }

    move(0, vel);
}
