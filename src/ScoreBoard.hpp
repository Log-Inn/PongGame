#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
# include "pong.hpp"
#include "player.hpp"
#include "ball.hpp"


class ScoreBoard : public sf::RectangleShape
{
private:
    double _score = 0;
    char side {};
    Player* self;
    Player* opp;
    Pong* window;

public:
    ScoreBoard(Player* p1,Player* p2,Pong* pg);
    void updateScore(Ball* ball);
    void getScore(char side);

    void createSprite(char* _side);
    void updateSprite();
    void EndScreen();
};

#endif // SCOREBOARD_HPP
