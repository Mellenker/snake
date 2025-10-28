#pragma once

#include "State.hpp"
#include "Application.hpp"
#include "Utils.hpp"
#include "PlayState.hpp"
#include "Context.hpp"
#include "SFML/Graphics.hpp"

class PauseState : public State {      
public:
    PauseState(sf::RenderWindow& window, Game& game);
    void processInput(Context& context) override;
    void update(Context& context) override;
    void render(Context& context) override;
private:
    Game& m_game;
};