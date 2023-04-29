#include "example_state.hpp"
#include "pong.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>


ExampleState::ExampleState(Pong *pongptr)
{
    m_program_ptr = pongptr;
    std::cout << "examplestate created\n";
}


ExampleState::~ExampleState() { std::cout << "examplestate destroyed\n"; }

void ExampleState::handleEvents(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            std::cout << "Hello World!\n";
        }
    }
}

void ExampleState::updateLogic(const float &dt) {}

void ExampleState::drawElements()
{
    sf::CircleShape cir(1000);
    cir.setFillColor(sf::Color::Blue);
    cir.setPosition(100, 100);
    draw(cir);
}

void ExampleState::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    m_program_ptr->getWindow()->draw(drawable, states);
}
