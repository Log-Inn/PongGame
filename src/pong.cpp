#include "pong.hpp"
#include "example_state.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <memory>


const sf::Vector2i DEFAULT_WIN_DIMS{1366, 768};
const int DEFAULT_FRAME_LIMIT = 120;

Pong::Pong()
    : m_window(sf::VideoMode(DEFAULT_WIN_DIMS.x, DEFAULT_WIN_DIMS.y), "Pong Game"),
      m_camera(static_cast<sf::Vector2f>(DEFAULT_WIN_DIMS / 2), static_cast<sf::Vector2f>(DEFAULT_WIN_DIMS)),
      m_clock(sf::Clock()), m_previous_time(), m_dt(0.0f)
{
    m_window.setFramerateLimit(DEFAULT_FRAME_LIMIT);
    // TODO: Remove this after testing. This sets the default state to the example state.
    //*Note: std::make_unique<ExampleState>(blahblah) is equivalent to doing new ExampleState(blahblah)
    m_state_manager.pushState(std::make_unique<ExampleState>(this));
}
Pong::~Pong() {}

void Pong::run()
{
    while (m_window.isOpen())
    {
        // Updates m_dt for use in physics / rendering purposes.
        // Must be called first
        updateDeltaTime();

        // Check for any inputs (polling events)
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            handleCommonEvents(event);
            m_state_manager.handleStateEvents(event);
        }

        // Update logic of the program.
        updateCommonLogic(m_dt);
        m_state_manager.updateStateLogic(m_dt);

        // Rendering
        drawCommonElements();
        m_state_manager.drawStateElements();
    }
}

sf::RenderWindow &Pong::getWindow() { return m_window; }

void Pong::updateDeltaTime()
{
    sf::Time current_time = m_clock.getElapsedTime();
    m_dt = (current_time - m_previous_time).asSeconds();
    m_previous_time = current_time;
}

void Pong::updateCommonLogic(const float &dt){};



void Pong::handleCommonEvents(const sf::Event &event)
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

void Pong::drawCommonElements()
{
    // Rendering
    m_window.clear();

    // draw() Commands Here:

    // Display the whatever you have drawn after m_window.clear();
    m_window.display();
}
