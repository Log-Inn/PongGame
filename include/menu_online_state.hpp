#ifndef MENU_ONLINE_STATE_HPP
#define MENU_ONLINE_STATE_HPP

#include "state_interface.hpp"
#include "textbox.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/TcpSocket.hpp>

class MenuOnline : public StateInterface
{

public:
    MenuOnline(Pong *pong_ptr);
    void handleEvents(sf::Event &event) override;
    void updateLogic(const float &dt) override;
    void drawElements() override;

private:
    sf::RenderWindow *m_window;
    sf::Font m_font;
    Textbox field_host_ip;
    Textbox field_host_port;

    std::unique_ptr<sf::TcpSocket> remote_client;

    // Use to prevent connection spamming
    bool m_connecting = false;

    void connect_to_host();
    void host_game();
};

#endif // MENU_ONLINE_STATE_HPP
