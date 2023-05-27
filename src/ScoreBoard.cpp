#include "entities/player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>
#include "scoreboard.hpp"

Scoreboard::Scoreboard()
{
    texture.loadFromFile("SBSprites\\SBScoreSprites.png");
    setTexture(texture);
    setOrigin(sf::Vector2f(s_width, s_height));
    setPosition(1366.0 / 4, 768.0 / 2);

}

void Scoreboard::initialize(Player* p1,Player* p2)
{
    self = p1;
    opp = p2;
}

void Scoreboard::updateScore(Ball* ball)
{

}

void Scoreboard::updateSprite()
{

}
