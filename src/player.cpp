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
void Player::create(char side, ControlScheme scheme)
{
    if (side == 'L')
    {
        _side = side;
        setPosition(50, 384);
    }
    else if (side == 'R')
    {
        _side = side;
        setPosition(1316, 384);
    }

    switch (scheme)
    {
    case WASD:
    {
        ascend = sf::Keyboard::W;
        descend = sf::Keyboard::S;
        break;
    }
    case ARROW:
    {
        ascend = sf::Keyboard::Up;
        descend = sf::Keyboard::Down;
        break;
    }
    case CPU:
        break;
    }
}

char Player::getSide() const { return _side; }

Player::MovementEvent Player::getPlayerMovementEvent(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == ascend)
        {
            return ASCEND_PRESSED;
        }
        else if (event.key.code == descend)
        {
            return DESCEND_PRESSED;
        }
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == ascend)
        {
            if (sf::Keyboard::isKeyPressed(descend))
            {
                return ASCEND_RELEASED_DESCEND_PRESSED;
            }
            else
            {
                return ASCEND_RELEASED;
            }
        }
        else if (event.key.code == descend)
        {
            if (sf::Keyboard::isKeyPressed(ascend))
            {
                return DESCEND_RELEASED_ASCEND_PRESSED;
            }
            else
            {
                return DESCEND_RELEASED;
            }
        }
    }
    return NAME;
}

// checks for input from player to go up or down or stop
void Player::updatePlayer(sf::Event &event) { updatePlayer(getPlayerMovementEvent(event)); }

void Player::updatePlayer(MovementEvent mv_event)
{
    switch (mv_event)
    {
    case ASCEND_PRESSED:
    {
        vel = -maxVel;
        break;
    }
    case ASCEND_RELEASED:
    {
        vel = 0;
        break;
    }
    case ASCEND_RELEASED_DESCEND_PRESSED:
    {
        vel = maxVel;
        break;
    }
    case DESCEND_RELEASED:
    {
        vel = 0;
        break;
    }
    case DESCEND_RELEASED_ASCEND_PRESSED:
    {
        vel = -maxVel;
        break;
    }
    case DESCEND_PRESSED:
    {
        vel = maxVel;
        break;
    }
    case NAME:
        break;
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
