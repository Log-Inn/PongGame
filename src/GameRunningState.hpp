#ifndef GAMERUNNINGSTATE_HPP
#define GAMERUNNINGSTATE_HPP

#include "entities/ball.hpp"
#include "entities/player.hpp"
#include "entities/cpu.hpp"
#include "state_interface.hpp"
#include "scoreboard.hpp"

class GameRunning : public StateInterface
{
    Player p1;
    CPU p2; // for Z
    // Player p2; // for Frost
    Ball ball;
    Scoreboard SB;

public:
    GameRunning(Pong *pong_ptr);
    void handleEvents(sf::Event &event) override;
    void updateLogic(const float &dt) override;
    void drawElements() override;

private:
    void collisionCheck();
    bool intersects(sf::CircleShape circle, sf::RectangleShape rect);
    /**
     * Convenience function to draw into pongptr's window

     * Equivalent to `m_program_ptr->getWindow().draw(drawable, states)`
     */
    void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);
};

#endif // GAMERUNNINGSTATE_HPP
