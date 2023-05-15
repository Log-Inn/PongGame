#include "GameRunningState.hpp"
#include "pong.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>


GameRunning::GameRunning(Pong *pong_ptr)
{
    m_program_ptr = pong_ptr;
    p1.create('L', Player::ControlScheme::WASD);
    p2.create('R', Player::ControlScheme::ARROW);
}

void GameRunning::handleEvents(sf::Event &event)
{
    p1.updatePlayer(event);
    p2.updatePlayer(event);
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

void GameRunning::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    m_program_ptr->getWindow()->draw(drawable, states);
}
