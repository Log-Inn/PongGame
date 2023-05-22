#ifndef GAMERUNNINGSTATE_HPP
#define GAMERUNNINGSTATE_HPP

#include "ball.hpp"
#include "player.hpp"
#include "state_interface.hpp"
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <thread>


class GameRunning : public StateInterface
{
    Player p1;
    Player p2;

    Ball ball;
    sf::Vector2f buffered_ball_pos;
    sf::Vector2f buffered_ball_vel;
    bool m_is_online;
    bool m_is_host;

    std::string remote_ip_str;
    unsigned short out_port;
    unsigned short in_port;
    sf::UdpSocket socket_sender;
    sf::UdpSocket socket_receiver;
    sf::Int32 curr_packet_number;
    // sf::Uint32 num_sent_packets;
    // Player::MovementEvent m_incoming_event;
    const sf::Time SYNC_PERIOD;
    sf::Time last_sync;
    sf::Clock sync_clock;

    // Use a dedicated thread to handle network loop to make it more performant
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
    void collisionCheck(const float &dt);
    bool intersects(sf::CircleShape circle, sf::RectangleShape rect);

    void initUDPSockets();
    void initNetworkLoop();

    void handleIncomingPackets();
    void sendPackets();
};

#endif // GAMERUNNINGSTATE_HPP
