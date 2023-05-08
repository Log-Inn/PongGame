#include "entities/player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include "scoreboard.hpp"


Scoreboard::Scoreboard(Player* p1,Player* p2,Pong* pg)
{
    self = p1;
    opp = p2;
    window = pg;
    texture.loadFromFile("SBSprites/BScoreSprite.png");
}


void Scoreboard::updateScore(Ball* ball){}
void Scoreboard::createSprite(char* _side){}

void Scoreboard::updateSprite(){}

void Scoreboard::EndScreen(){}