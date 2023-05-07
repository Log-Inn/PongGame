#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "ScoreBoard.hpp"

ScoreBoard::ScoreBoard(Player* p1,Player* p2)
{
    self = p1;
    opp = p2;
    sf::RectangleShape 
    sf::RectangleShape ScoreSpace;
    setSize(sf::Vector2f(width, height));
    setOrigin(width / 2, height / 2);
}


void ScoreBoard::updateScore(double vel){};
void ScoreBoard::getScore(char side){};

void ScoreBoard::createSprite(char* _side){};

void ScoreBoard::updateSprite(){};

void ScoreBoard::EndScreen(){};