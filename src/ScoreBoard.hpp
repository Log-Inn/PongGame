#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
# include "pong.hpp"
#include "player.hpp"


class ScoreBoard : public sf::RectangleShape
{
private:
    double _score = 0;
    char side {};
    Player* self;
    Player* opp;
    Pong* window;
    sf::RectangleShape ScoreWindow;
    sf::RectangleShape _zero;
    sf::RectangleShape _one;
    sf::RectangleShape _Zero;
    sf::RectangleShape _two;
    sf::RectangleShape _three;
    sf::RectangleShape _four;
    sf::RectangleShape _five;
    sf::RectangleShape _six;
    sf::RectangleShape _seven;
    sf::RectangleShape _eight;
    sf::RectangleShape _nine;
    

public:
    ScoreBoard(Player* p1,Player* p2,Pong* pg);
    void updateScore(double vel);
    void getScore(char side);

    void createSprite(char* _side);
    void updateSprite();
    void EndScreen();
};

#endif // SCOREBOARD_HPP
