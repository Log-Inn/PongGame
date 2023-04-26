#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @file pong.hpp
 * @brief This file contains the headers for the Pong class, which contains
 * general methods for the game pong.
 * @date 2023-04-26
 *
 * @copyright Copyright (c) 2023
 *
 */

/**                     Naming Scheme:

<---------------        private variables        --------------->
names start with m_ :           int m_number;
names are spaced by m_ :        int m_long_number;

<---------------         public variables        --------------->
names start with _ :            int _number;
names are spaced by _ :         int _long_number;

<---------------             methods             --------------->
names follow camelCase:         void doThisAndThat();
name
*/

class Pong
{
private:
    sf::RenderWindow m_window;
    sf::View m_camera;

public:
    Pong();
    ~Pong();
    /**
     * Runs the game, should only be called once.
     */
    void run();

private:
    void updateGameLogic();
    /**
     * Processes window events and inputs
     */
    void handleEvents(sf::Event &event);
};

#endif // WINDOW_HPP
