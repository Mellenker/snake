#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Context.hpp"
#include "Menu.hpp"

class PauseState : public State {      
public:
    PauseState(sf::RenderWindow& window, Game& game, Menu& menu);
    void processInput(Context& context) override;
    void update(Context& context) override;
    void render(Context& context) override;
private:
    Game& m_game;
    Menu& m_menu;
};