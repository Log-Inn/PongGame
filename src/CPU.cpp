#include "cpu.hpp"
# include "player.cpp"
#include <SFML/Graphics.hpp>

void CPU::create_AI(Player p1)
{
    if (p1.side == 'L')
    {
        this->setPosition(1025, 300);
    }
    else if (side == 'R')
    {
        this->setPosition(25, 300);
    }
}

void Player::movePlayer() { this->move(0, vel); }