#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include "pong.hpp"
#include "entities/player.hpp"
#include "entities/ball.hpp"


class Scoreboard:public sf::Sprite
{
private:
    double s_width  = 100;
    double s_height = 300;
    double WidthForSide = 300;
    sf::Texture texture;
    
    Player* self;
    Player* opp;

public:
    Scoreboard();
    void initialize(Player* p1,Player* p2);
    void updateScore(Ball* ball);
    void updateSprite();
};

#endif // SCOREBOARD_HPP
