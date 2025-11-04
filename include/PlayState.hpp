#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Context.hpp"
#include <SFML/System/Clock.hpp>

class PlayState : public State {      
public:
    PlayState(sf::RenderWindow& window, Game& game);
    void processInput(Context& context) override;
    void update(Context& context) override;
    void render(Context& context) override;
private:
    Game& m_game;
    sf::Clock m_moveClock;
    sf::Time m_moveInterval;
};