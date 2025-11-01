#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <optional>
#include "State.hpp"
#include "Game.hpp"

struct Context {    
    sf::Keyboard::Key keyPressed = sf::Keyboard::Key::Unknown;

    std::optional<PauseMenu::Action> pauseMenuAction;
    std::optional<GameOverMenu::Action> gameOverMenuAction;

    std::function<void(State::StateID id)> changeState;
};