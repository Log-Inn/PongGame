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
#include <iostream>
#include <memory>
#include <thread>

template <typename T> void logg(const T &msg) { std::cout << msg; }
template <typename T> void logg(const sf::Vector2<T> &msg) { std::cout << msg.x << "," << msg.y; }

sf::Packet &operator<<(sf::Packet &packet, const sf::Vector2f &vector) { return packet << vector.x << vector.y; }

sf::Packet &operator>>(sf::Packet &packet, sf::Vector2f &vector) { return packet >> vector.x >> vector.y; }

GameRunning::GameRunning(Pong *pong_ptr) : m_is_online(false)
{
    m_program_ptr = pong_ptr;
    p1.create('L', Player::ControlScheme::WASD);
    p2.create('R', Player::ControlScheme::ARROW);
}

GameRunning::GameRunning(Pong *pong_ptr, const bool &is_host, std::unique_ptr<sf::TcpSocket> &r_socket)
    : m_is_online(true), m_is_host(is_host), curr_packet_number(0), SYNC_PERIOD(sf::seconds(1.0f / 100))
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
    if (m_is_host)
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

    initUDPSockets();
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

void GameRunning::initUDPSockets()
{
    if (socket_receiver.bind(in_port) == sf::Socket::Done)
    {
        logg("UDP Listener binded to port: ");
        logg(in_port);
        logg("\n");
        socket_receiver.setBlocking(false);
        logg("Remote Target ");
        logg(remote_ip_str);
    }
    else
    {
        logg("Failed to bind UDP Socket to port: ");
        logg(in_port);
        logg("\n");
    }
}

void GameRunning::initNetworkLoop()
{
    m_network_thread_running = true;
    m_network_thread = std::make_unique<std::thread>(
        [&]()
        {
            while (m_network_thread_running)
            {
                auto current_time = sync_clock.getElapsedTime();
                if (current_time - last_sync >= SYNC_PERIOD)
                {
                    handleIncomingPackets();
                    sendPackets();
                    last_sync = current_time;
                }
            }
        });
};

void GameRunning::handleIncomingPackets()
{
    sf::Packet incoming;
    sf::IpAddress ip_addr{remote_ip_str};
    auto status = socket_receiver.receive(incoming, ip_addr, in_port);

    sf::Vector2f new_pos_player;
    sf::Vector2f new_pos_ball;
    sf::Vector2f new_vel_ball;
    sf::Int32 packet_time;
    incoming >> packet_time >> new_pos_player >> new_pos_ball >> new_vel_ball;

    // Drop old packets that arrive late
    if ((status == sf::Socket::Done) || (status == sf::Socket::Partial))
    {
        if (packet_time <= curr_packet_number)
        {
            logg("Packet ");
            logg(packet_time);
            logg("dropped. Expected > ");
            logg(curr_packet_number);
            logg("\n");
        }
        else
        {
            logg("Packet Received: ");
            logg(packet_time);
            logg("\n");
            curr_packet_number = packet_time;
            p2.setPosition(new_pos_player);
            if (!m_is_host)
            {
                // We do not set the ball's position directly here in order to not make it jittery
                // We will poll the buffered position BEFORE moving the ball on the client
                buffered_ball_pos = new_pos_ball;
                buffered_ball_vel = new_vel_ball;

                logg(new_pos_ball);
                logg("\n");
            }
        }
    }
}

void GameRunning::sendPackets()
{
    sf::Packet outgoing;
    outgoing << last_sync.asMilliseconds() << p1.getPosition() << ball.getPosition()
             << sf::Vector2f(ball.getXVel(), ball.getYVel());
    sf::IpAddress ip_addr{remote_ip_str};
    socket_sender.send(outgoing, ip_addr, out_port);
}

void GameRunning::handleEvents(sf::Event &event)
{
    if (m_is_online)
    {
        p1.updatePlayer(event);
    }
    else
    {
        p1.updatePlayer(event);
        p2.updatePlayer(event);
    }
}


void GameRunning::updateLogic(const float &dt)
{
    // if ball is scored, reset the ball to the centre
    if (ball.getGoal())
    {
        // add time delay here in the future
        ball.resetBall();
        buffered_ball_pos = ball.getPosition();
    }

    if (!m_is_online)
    {
        p2.movePlayer(dt);
    }
    else
    {
        // We buffer the ball's position for the client for it to look smooth.
        // The ball may look jittery if the network thread directly set the position of the ball.
        if (!m_is_host)
        {
            // ball.setPosition(buffered_ball_pos);
            ball.setXVel(buffered_ball_vel.x);
            ball.setYVel(buffered_ball_vel.y);

            // interpolate position for smoothness
            // TODO: Test whether using time since last sync is better.
            // NOTE: Current dt doesn't take into account last_sync

            sf::Vector2f prev_ball_pos = ball.getPosition();
            // float interpol_ratio = dt / SYNC_PERIOD.asSeconds();
            float interpol_ratio = (sync_clock.getElapsedTime() - last_sync).asSeconds() / SYNC_PERIOD.asSeconds();
            if (interpol_ratio < 1)
            {
                ball.setPosition(prev_ball_pos + (buffered_ball_pos - prev_ball_pos) * interpol_ratio);
            }
            else
            {
                ball.setPosition(buffered_ball_pos);
            }
        }
        ball.moveBall(dt);
        buffered_ball_pos = ball.getPosition();
    }

    p1.movePlayer(dt);

    collisionCheck(dt);
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
void GameRunning::collisionCheck(const float &dt)
{
    // Collision check done server sided
    // if ((!m_is_online) || (m_is_host))
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
        ball.collisionCheck(dt);

        // buffered_ball_vel.x = ball.getXVel();
        // buffered_ball_vel.y = ball.getYVel();
    }
}
