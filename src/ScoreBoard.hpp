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


class Scoreboard : public sf::Sprite
{
private:
    double sb_width;
    double sb_height; 
    
    sf::Sprite Score_L;
    sf::Sprite Score_R;
    sf::Texture texture;
    
    Player* self;
    Player* opp;
    Pong* window;

public:
    Scoreboard(Player* p1,Player* p2,Pong* pg);
    void updateScore(Ball* ball);

    void createSprite(char* _side);
    void updateSprite();
    void EndScreen();
};

#endif // SCOREBOARD_HPP
