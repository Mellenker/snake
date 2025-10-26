#pragma once

#include "Game.hpp"
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <optional>

struct Context {
    //Context();
    sf::Keyboard::Key keyPressed = sf::Keyboard::Key::Unknown;
    PauseMenu* pauseMenu = nullptr;
    GameOverMenu* gameOverMenu = nullptr;
    std::optional<PauseMenu::Action> pauseMenuAction;
    std::optional<GameOverMenu::Action> gameOverMenuAction;
    std::function<void(std::unique_ptr<State>)> changeState;
};
