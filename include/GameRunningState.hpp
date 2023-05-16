#ifndef GAMERUNNINGSTATE_HPP
#define GAMERUNNINGSTATE_HPP

#include "ball.hpp"
#include "player.hpp"
#include "state_interface.hpp"
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <thread>


class GameRunning : public StateInterface
{
    Player p1;
    Player p2;

    Ball ball;
    bool m_is_online;
    bool m_is_host;

    std::string remote_ip_str;
    unsigned short out_port;
    sf::UdpSocket socket_sender;
    sf::UdpSocket socket_receiver;
    bool has_sent = false;

    unsigned short in_port;

    Player::MovementEvent m_incoming_event;
    const sf::Time UPDATE_DELAY;
    sf::Clock clock;

    std::unique_ptr<std::thread> m_network_thread;
    bool m_network_thread_running;

public:
    // Creates an offline instance of the game
    GameRunning(Pong *pong_ptr);

    // Create an online instance of the game
    GameRunning(Pong *pong_ptr, const bool &is_host, std::unique_ptr<sf::TcpSocket> &r_socket);

    ~GameRunning();


    void handleEvents(sf::Event &event) override;
    void updateLogic(const float &dt) override;
    void drawElements() override;

private:
    void collisionCheck();
    bool intersects(sf::CircleShape circle, sf::RectangleShape rect);

    void init_socket();
    void handleIncomingPackets();
    void sendPackets();

    void initNetworkLoop();
};

#endif // GAMERUNNINGSTATE_HPP
