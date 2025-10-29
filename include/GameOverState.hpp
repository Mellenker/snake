#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Context.hpp"

class GameOverState : public State {      
public:
    GameOverState(sf::RenderWindow& window, Game& game);
    void processInput(Context& context) override;
    void update(Context& context) override;
    void render(Context& context) override;
private:
    Game& m_game;
};