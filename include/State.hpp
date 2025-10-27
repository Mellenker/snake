#pragma once

#include <SFML/Graphics.hpp>

// Forward-declare Context to avoid circular include with Context.hpp
struct Context;

class Application;

// Eventually make update return a request for state change instead of directly changing state.

class State {
public:
    State(sf::RenderWindow& window);
    virtual ~State() = default;

    virtual void processInput(Context& context) = 0;
    virtual void update(Context& context) = 0;
    virtual void render(Context& context) = 0;

protected:
    sf::RenderWindow& m_window;
};

