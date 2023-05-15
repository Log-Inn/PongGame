#ifndef STATE_HPP
#define STATE_HPP
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/Event.hpp>


class Pong;
class StateManager;

class StateInterface
{
protected:
    // Pointer to acccess app's memory
    Pong *m_program_ptr;
    StateManager *m_state_manager;

public:
    virtual ~StateInterface(){};


    virtual void handleEvents(sf::Event &event) = 0;
    virtual void updateLogic(const float &dt) = 0;
    virtual void drawElements() = 0;

    // Call this inside drawElements() to draw stuff
    void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);
};

#endif // STATE_HPP