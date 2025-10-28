#pragma once

#include "State.hpp"
#include "Application.hpp"
#include "Utils.hpp"
#include "PlayState.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"
#include "Context.hpp"
#include <memory>

class PlayState : public State {      
public:
    PlayState(sf::RenderWindow& window, Game& game, int inGameFpsLimit);
    void processInput(Context& context) override;
    void update(Context& context) override;
    void render(Context& context) override;
private:
    Game& m_game;
};