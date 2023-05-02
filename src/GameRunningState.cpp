#include "GameRunningState.hpp"
#include "pong.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>


GameRunning::GameRunning(Pong *pong_ptr)
{
    m_program_ptr = pong_ptr;
    p1.create('L');
    // p2.create('R');
    cpu.create_ai(p1);
}

void GameRunning::handleEvents(sf::Event &event)
{
    p1.updatePlayer(event);
    // p2.updatePlayer(event);
    // cpu.update_AI(p1);
}

void GameRunning::updateLogic(const float &dt)
{
    p1.movePlayer();
    // p2.movePlayer();
    //cpu.move_ai()
}

void GameRunning::drawElements()
{
    draw(p1);
    // draw(p2);
    // draw(cpu);
}

void GameRunning::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    m_program_ptr->getWindow()->draw(drawable, states);
}
