#include "state_interface.hpp"
#include "pong.hpp"
#include <iostream>
void StateInterface::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    if (m_program_ptr)
        m_program_ptr->getWindow()->draw(drawable, states);
    else
        std::cerr << "WARNING: m_program_ptr IS A NULLPTR. HAVE YOU INITIALIZED IT?\n";
}
