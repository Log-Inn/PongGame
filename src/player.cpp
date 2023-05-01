#include "player.hpp"
#include <SFML/Graphics.hpp>

Player::Player()
{
    this->setSize(sf::Vector2f(10, 70));
    this->setOrigin(5, 35);
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

void Player::moveUp() { this->move(0, -vel); }

void Player::moveDown() { this->move(0, vel); }
