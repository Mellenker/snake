#pragma once

#include "State.hpp"
#include "Application.hpp"
#include "Utils.hpp"
#include "PlayingState.hpp"
#include "Context.hpp"

class PauseState : public State {      
public:
    PauseState(PauseMenu& menu, Game& game, sf::RenderWindow& window);
    void processInput(Context& context) override;
    void update(Context& context) override;
    void render() override;
private:
    PauseMenu& menu;
    Game& game;
};