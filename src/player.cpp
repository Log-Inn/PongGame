#include "player.hpp"
#include <SFML/Graphics.hpp>

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
    }
    else if (side == 'R')
    {
        this->setPosition(1025, 300);
    }
}

void Player::movePlayer() { this->move(0, vel); }