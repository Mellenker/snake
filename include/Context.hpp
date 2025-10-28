#pragma once

#include "Game.hpp"
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <optional>

struct Context {
    PauseMenu* pauseMenu = nullptr;

    GameOverMenu* gameOverMenu = nullptr;
    
    sf::Keyboard::Key keyPressed = sf::Keyboard::Key::Unknown;
    std::optional<PauseMenu::Action> pauseMenuAction;
    std::optional<GameOverMenu::Action> gameOverMenuAction;

    std::function<void(State::StateID id)> changeState;
};
