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
};

#endif // EXAMPLE_STATE_HPP
