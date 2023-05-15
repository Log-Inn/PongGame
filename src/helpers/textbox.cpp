//
//  Textbox.cpp
//  SFML Textbox
//
//  Created by Thomas Redding on 9/12/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "textbox.hpp"
#include <SFML/System/Vector2.hpp>

/********** -------------- **********/
/********** Public Methods **********/
/********** -------------- **********/


Textbox::Textbox(sf::RenderWindow &windowToUse, sf::Font &fontToUse) : font(fontToUse), window(windowToUse)
{
    text = sf::Text("", font);
    background.setFillColor(sf::Color::White);
    text.setFillColor(sf::Color::Red);
}

void Textbox::draw()
{
    window.draw(background);
    window.draw(text);
}

void Textbox::setDimensons(double newX, double newY, double newWidth, double newHeight)
{
    x = newX;
    y = newY;
    width = newWidth;
    height = newHeight;
    text.setPosition(x, y - height / 5);
    text.setCharacterSize(height);
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(width, height));
}

void Textbox::setString(std::string newString)
{
    string = newString;
    text.setString(string);
}

std::string Textbox::getString() { return string; }

bool Textbox::pollEvent(sf::Event event)
{
    if (isFocused)
    {
        if (event.type == sf::Event::TextEntered)
            return enterText(event.text.unicode);
    }
    return false;
}

void Textbox::setFocus(bool newFocus) { isFocused = newFocus; }

bool Textbox::isMouseOver(const sf::Vector2f &mousePos) { return background.getGlobalBounds().contains(mousePos); }

/********** --------------- **********/
/********** Private Methods **********/
/********** --------------- **********/

bool Textbox::enterText(sf::Uint32 unicode)
{
    if (unicode == 8)
        string = string.substr(0, string.length() - 1); // delete key
    else if (unicode == 10)
        return true;                                    // return key
    else
        string += (char)unicode;
    text.setString(string);
    return false;
}
