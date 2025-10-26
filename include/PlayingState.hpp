#pragma once

#include "State.hpp"
#include "Application.hpp"
#include "Utils.hpp"
#include "PlayingState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "Context.hpp"
#include <memory>

class PlayingState : public State {      
public:
    PlayingState(sf::RenderWindow& window, Game& game);
    void processInput(Context& context) override;
    void update(Context& context) override;
    void render(Context& context) override;
private:
    Game& game;
};