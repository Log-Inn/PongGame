#include "menu_online_state.hpp"
#include "GameRunningState.hpp"
#include "pong.hpp"
#include "state_manager.hpp"
#include "textbox.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

template <typename T> void logg(const T &msg) { std::cout << msg; };

MenuOnline::MenuOnline(Pong *pong_ptr)
    : field_host_ip(*(pong_ptr->getWindow()), m_font), field_host_port(*(pong_ptr->getWindow()), m_font)
{
    m_program_ptr = pong_ptr;
    m_state_manager = &pong_ptr->m_state_manager;
    m_window = pong_ptr->getWindow();
    m_font.loadFromFile("assets/arial.ttf");

    // Can set field_host_ip return event to transition states
    field_host_ip.setDimensons(100, 100, 200, 30);
    field_host_ip.setFocus(false);

    field_host_port.setDimensons(100, 200, 100, 30);
    field_host_port.setFocus(false);

    remote_client = std::make_unique<sf::TcpSocket>();
}

void MenuOnline::handleEvents(sf::Event &event)
{
    // TODO: Make Menu Handler Class
    field_host_ip.pollEvent(event);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window));
        if (field_host_ip.isMouseOver(mousePos))
        {
            field_host_ip.setFocus(true);
        }
        else
        {
            field_host_ip.setFocus(false);
        }
    }

    field_host_port.pollEvent(event);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window));
        if (field_host_port.isMouseOver(mousePos))
        {
            field_host_port.setFocus(true);
        }
        else
        {
            field_host_port.setFocus(false);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window));
        if (field_host_ip.isMouseOver(mousePos))
        {
            if (!m_connecting)
                connect_to_host();
        }
        if (field_host_port.isMouseOver(mousePos))
        {
            if (!m_connecting)
                host_game();
        }
    }
}

void MenuOnline::updateLogic(const float &dt) {}

void MenuOnline::drawElements()
{
    field_host_port.draw();
    field_host_ip.draw();
}

void MenuOnline::connect_to_host()
{
    m_connecting = true;
    std::unique_ptr<sf::TcpSocket> client = std::make_unique<sf::TcpSocket>();
    client->setBlocking(true);
    auto hostip = field_host_ip.getString();
    int hostport;
    if (field_host_port.getString().length() > 0)
    {
        hostport = std::stoi(field_host_port.getString());
    }
    else
    {
        hostport = 7777;
    }

    if (hostip.empty())
    {
        hostip = "127.0.0.1";
    }

    logg("Connecting to host...\n");
    if (client->connect(hostip, hostport, sf::seconds(5)) != sf::Socket::Done)
    {
        logg("Connection Failed\n");
        m_connecting = false;
        return;
    }
    logg("Connection Established\n");

    // Pass a TCP connection
    remote_client = std::move(client);

    // Initiate state change
    m_state_manager->changeState(std::make_unique<GameRunning>(m_program_ptr, false, remote_client));
}

void MenuOnline::host_game()
{
    m_connecting = true;

    sf::TcpListener listener;
    listener.listen(std::stoi(field_host_port.getString()));
    logg("Listener Started\n");

    while (true)
    {
        // Accept new connections
        if (listener.accept(*remote_client) == sf::Socket::Done)
        {
            logg("New client connected\n");
            break;
        }
    }

    logg(remote_client->getRemoteAddress());
    logg("\n");

    // Return only when new connection is established
    // Initiate state change
    m_state_manager->changeState(std::make_unique<GameRunning>(m_program_ptr, true, remote_client));
}