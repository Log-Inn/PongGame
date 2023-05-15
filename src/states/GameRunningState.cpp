#include "GameRunningState.hpp"
#include "player.hpp"
#include "pong.hpp"
#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>

template <typename T> void logg(const T &msg) { std::cout << msg; }

// sf::Packet &operator<<(sf::Packet &packet, const Player::MovementEvent &movementEvent)
// {
//     return packet << static_cast<sf::Int16>(movementEvent);
// }

// sf::Packet &operator>>(sf::Packet &packet, Player::MovementEvent &movementEvent)
// {
//     sf::Int16 value;
//     packet >> value;
//     movementEvent = static_cast<Player::MovementEvent>(value);
//     logg("Unpacked value ");
//     logg(value);
//     logg(" into ");
//     logg(movementEvent);
//     logg("\n");


//     return packet;
// }

GameRunning::GameRunning(Pong *pong_ptr) : m_is_online(false)
{
    m_program_ptr = pong_ptr;
    p1.create('L', Player::ControlScheme::WASD);
    p2.create('R', Player::ControlScheme::ARROW);
}

GameRunning::GameRunning(Pong *pong_ptr, const bool &is_host, std::unique_ptr<sf::TcpSocket> &r_socket)
    : m_is_online(true)
{
    m_program_ptr = pong_ptr;
    {
        auto remote_socket = std::move(r_socket);
        remote_ip = remote_socket->getRemoteAddress();
        out_port = remote_socket->getRemotePort();
    }

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
}

void GameRunning::init_socket()
{
    if (socket_udp_in.bind(in_port) == sf::Socket::Done)
    {
        logg("UDP Listener binded to port: ");
        logg(in_port);
        logg("\n");
        socket_udp_in.setBlocking(false);
    }
    else
    {
        logg("Failed to bind UDP Socket to port: ");
        logg(in_port);
        logg("\n");
    }

    if (socket_udp_out.bind(out_port) == sf::Socket::Done)
    {
        logg("UDP Sender binded to port: ");
        logg(out_port);
        logg("\n");
        socket_udp_out.setBlocking(false);
    }
    else
    {
        logg("Failed to bind UDP Socket to port: ");
        logg(out_port);
        logg("\n");
    }
}

void GameRunning::handleIncomingPackets()
{
    sf::Packet incoming;
    socket_udp_in.receive(incoming, remote_ip, in_port);
    sf::Int16 temp;

    incoming >> temp;
    m_incoming_event = static_cast<Player::MovementEvent>(temp);
    if (m_incoming_event > 0)
    {
        logg("Packet Received\n");
        logg(m_incoming_event);
        logg("\n");
        p2.updatePlayer(m_incoming_event);
    }
}

void GameRunning::sendPackets(sf::Event &event)
{
    sf::Packet outgoing;
    sf::Int16 ev = p1.getPlayerMovementEvent(event);
    if (ev != Player::MovementEvent::NAME)
    {
        outgoing << ev;
        if (socket_udp_out.send(outgoing, remote_ip, out_port))
        {
            logg("Packet Sent\n");
            logg(ev);
            logg("\n");
        }
    }

    //
}

// Untidy, but network events will be handled inside of handle events.
// Better to refactor state interface for a dedicated handleIncomingPackets() and sendPackets()
void GameRunning::handleEvents(sf::Event &event)
{
    handleIncomingPackets();
    sendPackets(event);
    p1.updatePlayer(event);
}

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
