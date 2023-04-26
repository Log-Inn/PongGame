#include "pong.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

const sf::Vector2i DEFAULT_WIN_DIMS{1366, 768};
const int DEFAULT_FRAME_LIMIT = 120;

Pong::Pong()
    : m_window(sf::VideoMode(DEFAULT_WIN_DIMS.x, DEFAULT_WIN_DIMS.y),
               "Pong Game"),
      m_camera(static_cast<sf::Vector2f>(DEFAULT_WIN_DIMS / 2),
               static_cast<sf::Vector2f>(DEFAULT_WIN_DIMS))
{
    m_window.setFramerateLimit(DEFAULT_FRAME_LIMIT);
}
Pong::~Pong() {}

void Pong::run()
{
    while (m_window.isOpen())
    {
        // Check for any inputs (polling events)
        sf::Event event;
        handleEvents(event);

        // Update logic of the program
        updateGameLogic();

        // Rendering
        m_window.clear();

        // draw() Commands Here:

        // Display the whatever you have drawn after m_window.clear();
        m_window.display();
    }
}

void Pong::updateGameLogic() {}

void Pong::handleEvents(sf::Event &event)
{
    // We put this in a while loop to ensure that the events are polled
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_window.close();
            }
        }
    }
}
