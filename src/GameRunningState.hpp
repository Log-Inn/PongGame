#ifndef GAMERUNNINGSTATE_HPP
#define GAMERUNNINGSTATE_HPP

#include "ball.hpp"
#include "player.hpp"
#include "state_interface.hpp"



class GameRunning : public StateInterface
{
    Player p1;
    Player p2;
    Ball ball;

public:
    GameRunning(Pong *pong_ptr);
    void handleEvents(sf::Event &event) override;
    void updateLogic(const float &dt) override;
    void drawElements() override;

private:
    void paddleCollisionCheck();
    bool intersects(sf::CircleShape circle, sf::RectangleShape rect);
    /**
     * Convenience function to draw into pongptr's window

     * Equivalent to `m_program_ptr->getWindow().draw(drawable, states)`
     */
    void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);
};

#endif // GAMERUNNINGSTATE_HPP
