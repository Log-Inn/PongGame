#include "GameRunningState.hpp"
#include "pong.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>


GameRunning::GameRunning(Pong *pong_ptr)
{
    m_program_ptr = pong_ptr;
    p1.create('L');
    cpu.create_AI(p1);
}

void GameRunning::handleEvents(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            p1.acc = -0.1;
            std::cout << p1.acc;
        }
        else if (event.key.code == sf::Keyboard::S)
        {
            p1.acc = 0.1;
            std::cout << p1.acc;
        }
    }
}

void GameRunning::updateLogic(const float &dt)
{
    if (p1.vel <= 10)
    {
        p1.vel += p1.acc;
    }
    if (p1.getPosition().y <= p1.height / 2)
    {
        p1.vel = 0;
    }
    p1.movePlayer();
}

void GameRunning::drawElements() { draw(p1); }

void GameRunning::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    m_program_ptr->getWindow()->draw(drawable, states);
}
