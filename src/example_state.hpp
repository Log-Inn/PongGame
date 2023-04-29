#ifndef EXAMPLE_STATE_HPP
#define EXAMPLE_STATE_HPP
#include "state_interface.hpp"
#include <SFML/Graphics/Drawable.hpp>
class ExampleState : public StateInterface
{
public:
    explicit ExampleState(Pong *pongptr);
    virtual ~ExampleState() override;

    virtual void handleEvents(sf::Event &event) override;
    virtual void updateLogic(const float &dt) override;
    virtual void drawElements() override;

private:
    /**
     * Convenience function to draw into pongptr's window

     * Equivalent to `m_program_ptr->getWindow().draw(drawable, states)`
     */
    void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);
};

#endif // EXAMPLE_STATE_HPP
