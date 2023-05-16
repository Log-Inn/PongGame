#include "GameRunningState.hpp"
#include "player.hpp"
#include "pong.hpp"
#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>

template <typename T> void logg(const T &msg) { std::cout << msg; }
template <typename T> void logg(const sf::Vector2<T> &msg) { std::cout << msg.x << "," << msg.y; }



GameRunning::GameRunning(Pong *pong_ptr) : m_is_online(false)
{
    m_program_ptr = pong_ptr;
    p1.create('L', Player::ControlScheme::WASD);
    p2.create('R', Player::ControlScheme::ARROW);
}

GameRunning::GameRunning(Pong *pong_ptr, const bool &is_host, std::unique_ptr<sf::TcpSocket> &r_socket)
    : m_is_online(true), m_is_host(is_host), UPDATE_DELAY(sf::seconds(1.0f / 30))
{
    m_program_ptr = pong_ptr;

    std::unique_ptr<sf::TcpSocket> remote_socket = std::move(r_socket);
    remote_ip_str = remote_socket->getRemoteAddress().toString();
    in_port = remote_socket->getRemotePort();

    logg("Connection received from: ");
    logg(remote_ip_str);
    logg(":");
    logg(in_port);
    logg("\n");

    // Initialise server / synchronise connections
    // Positions will be host authoritative
    // P1 will be the
    if (is_host)
    {
        logg("host config initialised\n");
        p1.create('L', Player::ControlScheme::WASD);
        p2.create('R', Player::ControlScheme::ARROW);
        in_port = 7777;
        out_port = 7778;
    }
    else
    {
        logg("client config initialised\n");
        p1.create('R', Player::ControlScheme::WASD);
        p2.create('L', Player::ControlScheme::ARROW);
        in_port = 7778;
        out_port = 7777;
    }

    init_socket();
    initNetworkLoop();
}

GameRunning::~GameRunning()
{
    if (m_network_thread)
    {
        m_network_thread_running = false;
        m_network_thread->join();
    }
}

void GameRunning::init_socket()
{
    if (socket_receiver.bind(in_port) == sf::Socket::Done)
    {
        logg("UDP Listener binded to port: ");
        logg(in_port);
        logg("\n");
        socket_receiver.setBlocking(false);
    }
    else
    {
        logg("Failed to bind UDP Socket to port: ");
        logg(in_port);
        logg("\n");
    }
}

void GameRunning::handleIncomingPackets()
{
    sf::Packet incoming;
    sf::IpAddress ip_addr{remote_ip_str};
    auto status = socket_receiver.receive(incoming, ip_addr, in_port);

    sf::Vector2f new_pos;
    incoming >> new_pos.x >> new_pos.y;

    if ((status == sf::Socket::Done) || (status == sf::Socket::Partial))
    {
        logg("Packet Received\n");
        logg(new_pos);
        logg("\n");
        p2.setPosition(new_pos);
    }
}

void GameRunning::sendPackets()
{
    sf::Packet outgoing;

    outgoing << p1.getPosition().x << p1.getPosition().y;
    sf::IpAddress ip_addr{remote_ip_str};
    socket_sender.send(outgoing, ip_addr, out_port);
    {
        logg("Packet Sent to: ");
        logg(remote_ip_str);
        logg(":");
        logg(out_port);
        logg("\n");
    }
}

// Untidy, but network events will bSe handled inside of handle events.
// Better to refactor state interface for a dedicated handleIncomingPackets() and sendPackets()
void GameRunning::handleEvents(sf::Event &event) { p1.updatePlayer(event); }

void GameRunning::initNetworkLoop()
{
    m_network_thread_running = true;
    m_network_thread = std::make_unique<std::thread>(
        [&]()
        {
            while (m_network_thread_running)
            {
                if (clock.getElapsedTime() >= UPDATE_DELAY)
                {
                    // std::thread receiveThread([&]() { handleIncomingPackets(); });
                    // std::thread sendThread([&]() { sendPackets(); });
                    if (has_sent)
                    {
                        sendPackets();
                    }
                    else
                    {
                        handleIncomingPackets();
                    }
                    has_sent = !has_sent;
                    clock.restart();

                    // receiveThread.join();
                    // sendThread.join();
                }
            }
        });
};

void GameRunning::updateLogic(const float &dt)
{
    // if ball is scored, reset the ball to the centre
    if (ball.getGoal())
    {
        // add time delay here in the future
        ball.resetBall();
    }

    p1.movePlayer();
    p2.movePlayer();

    collisionCheck();
    ball.moveBall();
}

void GameRunning::drawElements()
{
    draw(p1);
    draw(p2);
    draw(ball);
}

// courtesy of https://stackoverflow.com/users/33686/e-james
bool GameRunning::intersects(sf::CircleShape circle, sf::RectangleShape rect)
{
    sf::Vector2f circleDistance(abs(circle.getPosition().x - rect.getPosition().x),
                                abs(circle.getPosition().y - rect.getPosition().y));

    if (circleDistance.x > (rect.getSize().x / 2 + circle.getRadius()))
    {
        return false;
    }
    if (circleDistance.y > (rect.getSize().y / 2 + circle.getRadius()))
    {
        return false;
    }

    if (circleDistance.x <= (rect.getSize().x / 2))
    {
        return true;
    }
    if (circleDistance.y <= (rect.getSize().y / 2))
    {
        return true;
    }

    double cornerDistance_sq =
        pow((circleDistance.x - rect.getSize().x / 2), 2) + pow((circleDistance.y - rect.getSize().y / 2), 2);

    return (cornerDistance_sq <= pow(circle.getRadius(), 2));
}

// If intersects, ball is pushed outside the paddle and vel is flipped, acc is added. yvel is changed slightly
void GameRunning::collisionCheck()
{
    Player &leftPlayer = (p1.getSide() == 'L') ? p1 : p2;
    Player &rightPlayer = (p1.getSide() == 'L') ? p2 : p1;

    if (p1.getSide() == 'L')
    {
        leftPlayer = p1;
        rightPlayer = p2;
    }
    else
    {
        leftPlayer = p2;
        rightPlayer = p1;
    }
    // paddle collision check, Left Player
    if (intersects(ball, leftPlayer))
    {
        // ball pushed out of paddle
        ball.setPosition(leftPlayer.getPosition().x + leftPlayer.getWidth() / 2 + ball.getRadius(), ball.getY());
        ball.setXVel(-ball.getXVel() + ball.getAcc());

        // y_delta is the change in y_vel based on where the ball hits relative to centre of paddle.
        // Max y_delta magnitude is paddle height/2.
        // y_delta is rescaled to within -4 to 4 by multiplying by 4/(paddle height/2) = 8/paddle_height
        // ball's y vel is capped out at max y vel in ball class
        double y_delta = (ball.getY() - leftPlayer.getPosition().y) * 8 / leftPlayer.getHeight();

        // y vel limited to max y vel magnitude
        double newVel = ball.getYVel() + y_delta;
        if ((abs(newVel) < ball.getMaxYVel()))
        {
            ball.setYVel(newVel);
        }
        else
        {
            if (newVel > 0)
            {
                ball.setYVel(ball.getMaxYVel());
            }
            else
            {
                ball.setYVel(-ball.getMaxYVel());
            }
        }
    }

    // paddle collision check, RightPlayer
    else if (intersects(ball, rightPlayer))
    {
        ball.setPosition(rightPlayer.getPosition().x - rightPlayer.getWidth() / 2 - ball.getRadius(), ball.getY());
        ball.setXVel(-ball.getXVel() - ball.getAcc());
        double y_delta = (ball.getY() - rightPlayer.getPosition().y) * 8 / rightPlayer.getHeight();

        double newVel = ball.getYVel() + y_delta;
        if ((abs(newVel) < ball.getMaxYVel()))
        {
            ball.setYVel(newVel);
        }
        else
        {
            if (newVel > 0)
            {
                ball.setYVel(ball.getMaxYVel());
            }
            else
            {
                ball.setYVel(-ball.getMaxYVel());
            }
        }
    }

    // collision check with borders
    ball.collisionCheck();
}
