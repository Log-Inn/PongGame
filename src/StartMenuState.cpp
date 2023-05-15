#include "StartMenuState.hpp"

StartMenu::StartMenu(Pong *pong_ptr)

{
    m_program_ptr = pong_ptr;
    // Create buttons and assets
}

void StartMenu::handleEvents(sf::Event &event)
{
    // Check for menu button presses
}

void StartMenu::updateLogic(const float &dt) {}

void StartMenu::drawElements()
{
    // Buttons
}
