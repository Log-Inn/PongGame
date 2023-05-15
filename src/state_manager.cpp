#include "state_manager.hpp"
#include <iostream>
template <typename T> void logg(const T &msg) { std::cout << msg; };

StateManager::StateManager() : m_add(false), m_replace(false), m_remove(false) {}

StateManager::~StateManager() {}
void StateManager::pushState(std::unique_ptr<StateInterface> newstate)
{
    logg("state push queued\n");
    m_add = true;
    m_new_state = std::move(newstate);
    // m_stack.push(std::move(newstate));
}

void StateManager::popState()
{
    logg("state pop queued\n");
    m_remove = true;
    // m_stack.pop();
}

void StateManager::changeState(std::unique_ptr<StateInterface> newstate)
{
    m_stack.pop();
    m_stack.push(std::move(newstate));
}

void StateManager::processStateChange()
{
    // log("processing state changes\n");
    if (m_remove && (!m_stack.empty()))
    {
        logg("popped state\n");
        m_stack.pop();
        //? Maybe we should add an explicit start running State code here?
        m_remove = false;
    }

    if (m_add)
    {
        logg("pushed state\n");
        if (m_replace && (!m_stack.empty()))
        {
            m_stack.pop();
            m_replace = false;
        }

        //? Likewise, should we add an explicit call to pause the previous state code?

        m_stack.push(std::move(m_new_state));
        //? Perhaps also add a way to init states?
        //? and start here too perhaps?
        m_add = false;
    }
}

void StateManager::handleStateEvents(sf::Event &event)
{
    if (!m_stack.empty())
    {
        m_stack.top()->handleEvents(event);
    }
    else
    {
        std::cerr << "WARNING: NO STATES ARE PRESENT IN THE STATE MANAGER, CALL TO handleStateEvents() SKIPPED.\n";
    }
}

void StateManager::updateStateLogic(const float &dt)
{
    if (!m_stack.empty())
    {
        m_stack.top()->updateLogic(dt);
    }
    else
    {
        std::cerr << "WARNING: NO STATES ARE PRESENT IN THE STATE MANAGER, CALL TO updateStateLogic() SKIPPED.\n";
    }
}

void StateManager::drawStateElements()
{
    if (!m_stack.empty())
    {
        m_stack.top()->drawElements();
    }
    else
    {
        std::cerr << "WARNING: NO STATES ARE PRESENT IN THE STATE MANAGER, CALL TO drawStateElements() SKIPPED.\n";
    }
}
