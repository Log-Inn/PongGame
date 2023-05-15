#ifndef GAMERUNNINGSTATE_HPP
#define GAMERUNNINGSTATE_HPP

#include "ball.hpp"
#include "player.hpp"
#include "state_interface.hpp"
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <memory>



class GameRunning : public StateInterface
{
    Player p1;
    Player p2;

    Ball ball;
    bool m_is_online;
    bool m_is_host;

    sf::IpAddress remote_ip;
    int remote_port;
    std::unique_ptr<sf::UdpSocket> local_udp_socket;
    std::unique_ptr<sf::UdpSocket> remote_udp_socket;

public:
    // Creates an offline instance of the game
    GameRunning(Pong *pong_ptr);

    // Create an online instance of the game
    GameRunning(Pong *pong_ptr, const bool &is_host, std::unique_ptr<sf::TcpSocket> &r_socket);


    void handleEvents(sf::Event &event) override;
    void updateLogic(const float &dt) override;
    void drawElements() override;

private:
    void collisionCheck();
    bool intersects(sf::CircleShape circle, sf::RectangleShape rect);
};

#endif // GAMERUNNINGSTATE_HPP
