#include "GameRunningState.hpp"
#include "pong.hpp"
#include <SFML/Graphics/CircleShape.hpp>


GameRunning::GameRunning(Pong *pong_ptr)
{
    p1.create('L');
    p2.create('R');
}

void GameRunning::handleEvents(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            p1.acc = -0.1;
        }
    }
}

void GameRunning::updateLogic(const float &dt) { p1.vel += p1.acc; }

void GameRunning::drawElements() { draw(sf::CircleShape(100)); }

void GameRunning::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    m_program_ptr->getWindow()->draw(drawable, states);
}
