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

/*                      Naming Scheme:
 *
 * <---------------        private variables        --------------->
 * names start with m_ :           int m_number;
 * names are spaced by m_ :        int m_long_number;
 *
 * <---------------         public variables        --------------->
 * names start with _ :            int _number;
 * names are spaced by _ :         int _long_number;
 *
 * <---------------             methods             --------------->
 * names follow camelCase:         void doThisAndThat();
 * name
 */


/*
 * Below are the different states for the game.
 * Note that a states here refers to a different sections of the program:
 * E.G. when you are completely switching over to drawing a different thing,
 * and running a different part of the code.
 */
//* Game State Explanations
//* MENU_MAIN,     Select between Singleplayer, Multiplayer, Options Menu, or Quit
//* MENU_OPTIONS,  Customize some shit I guess?
//* MENU_CONNECT,  Menu that have HOST and JOIN as options.
//* MENU_HOST,     Menu to wait for hosts to wait for incoming connections.
//* MENU_JOIN,     Menu to input ip and shit to connect to a host's game.
//* GAME_RUNNING,  Run game. Game should have a single / multiplayer toggle. Upon game over prompt restart menu.
//* GAME_PAUSED    Overlay menu which pauses the game. Give option to quit.



// TODO: Add a StateManager class into Pong, Pong::run() method should call the StateManager::handleEvents
class Pong
{
private:
    sf::RenderWindow m_window;
    sf::View m_camera;
    sf::Clock m_clock;
    sf::Time m_previous_time;
    // Time Step Between Frames in seconds
    float m_dt;

public:
    Pong();
    ~Pong();
    /**
     * Runs the game, should only be called once.
     * Contains the game loop.
     */
    void run();

private:
    void updateDeltaTime();
    /**
     * Updates the common logic based on the current state of the game.
     */
    void updateCommonLogic(const float &dt);
    /**
     * Processes individual events and inputs AFTER it is polled.
     * This needs to be inside the while(pollevents()) loop.
     * Events handled here should contain only common events regardless of gamestate.
     */
    void handleCommonEvents(const sf::Event &event);
};

#endif // WINDOW_HPP
