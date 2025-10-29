#pragma once
#include <SFML/Graphics.hpp>

struct Context; // Forward declaration

class State {
public:
    State(sf::RenderWindow& window);
    virtual ~State() = default;

    enum class StateID {
        PLAY,
        PAUSE,
        GAME_OVER
    };
    
    virtual void processInput(Context& context) = 0;
    virtual void update(Context& context) = 0;
    virtual void render(Context& context) = 0;

protected:
    sf::RenderWindow& m_window;
};

