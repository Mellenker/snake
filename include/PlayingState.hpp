#pragma once

#include "State.hpp"
#include "Application.hpp"
#include "Utils.hpp"
#include "PlayingState.hpp"
#include "Context.hpp"

class PlayingState : public State {      
public:
    PlayingState(sf::RenderWindow& window, Game& game);
    void processInput(Context& context) override;
    void update(Context& context) override;
    void render() override;
private:
    Game& game;
};