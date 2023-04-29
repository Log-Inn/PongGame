#ifndef STATE_HPP
#define STATE_HPP
#include <SFML/Window/Event.hpp>

class Pong;

class StateInterface
{
protected:
    // Pointer to acccess app's memory
    Pong *m_program_ptr;

public:
    virtual ~StateInterface(){};


    virtual void handleEvents(sf::Event &event) = 0;
    virtual void updateLogic(const float &dt) = 0;
    virtual void drawElements() = 0;
    /*TODO: add method `draw()` that does the following:
    `
        void ExampleState::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
        {
            m_program_ptr->getWindow().draw(drawable, states);
        }
    `
    */
};

#endif // STATE_HPP
