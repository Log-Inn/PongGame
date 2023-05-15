#ifndef STARTMENUSTATE_HPP
#define STARTMENUSTATE_HPP

#include "state_interface.hpp"

class StartMenu : public StateInterface
{
public:
    StartMenu(Pong *pong_ptr);
    void handleEvents(sf::Event &event) override;
    void updateLogic(const float &dt) override;
    void drawElements() override;

private:
};

#endif // STARTMENUSTATE_HPP
