#include "GameRunningState.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>


GameRunning::GameRunning(Pong *pong_ptr)
{
    m_program_ptr = pong_ptr;
    p1.hookWindow(pong_ptr);
    p1.create('L');
    // p2.create('R');
    cpu.hookWindow(pong_ptr);
    cpu.createCpu(&p1);
}

void GameRunning::handleEvents(sf::Event &event)
{
    p1.updatePlayer(event);
    std::cout<< "Diff in pos between CPU and P1 is "<<cpu.getPDisp('y');
    // p2.updatePlayer(event);
    // cpu.updateCpu();
}

void GameRunning::updateLogic(const float &dt)
{
    if (ball.goalScored())
    {
        // add time delay here in the future
        ball.resetBall();
    }
    p1.movePlayer();
    // cpu.movePlayer();
    // p2.movePlayer();
    //paddleCollisionCheck();
    ball.moveBall();
}

void GameRunning::drawElements()
{
    draw(p1);
    // draw(p2);
    draw(cpu);
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

// need to fix this shit
// Zpm: GG bro
// ! Zpm: Turn collision back on once we fix this
// void GameRunning::paddleCollisionCheck()
// {
//     if (intersects(ball, p1) || intersects(ball, p2))
//     {
//         ball.setXVel(-ball.getXVel());
//     }
// }

void GameRunning::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    m_program_ptr->getWindow()->draw(drawable, states);
}
