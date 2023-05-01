#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP
#include "state_interface.hpp"
#include <memory>
#include <stack>


class StateManager
{
private:
    std::stack<std::unique_ptr<StateInterface>> m_stack;
    bool m_add;
    bool m_replace;
    bool m_remove;
    std::unique_ptr<StateInterface> m_new_state;

public:
    StateManager();
    ~StateManager();

    /**
     * Adds a new state without removing the previous one.
     * Use if you want to preserve the data of the previous state.
     * Note that operations only proceed after `processStateChanges()` is called.
     */
    void pushState(std::unique_ptr<StateInterface> newstate);
    /**
     * Removes the current state, returning to the previous one.
     * Note that the removed state will have it's data wiped
     * Note that operations only proceed after `processStateChanges()` is called.
     */
    void popState();
    /**
     * Changes the current state to a different one.
     * Note that the data in the current state will be wiped.
     * Equivalent to calling `popState(); pushState(newState);`
     * Note that operations only proceed after `processStateChanges()` is called.
     */
    void changeState(std::unique_ptr<StateInterface> newstate);

    void processStateChange();

    void handleStateEvents(sf::Event &event);
    void updateStateLogic(const float &dt);
    void drawStateElements();
};

#endif // STATEMANAGER_HPP
