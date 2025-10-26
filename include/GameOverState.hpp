#pragma once

#include "State.hpp"
#include "Application.hpp"
#include "Utils.hpp"
#include "PlayingState.hpp"
#include "Context.hpp"
#include "SFML/Graphics.hpp"

class GameOverState : public State {      
public:
    GameOverState(sf::RenderWindow& window, Game& game);
    void processInput(Context& context) override;
    void update(Context& context) override;
    void render(Context& context) override;
private:
    Game& game;
};