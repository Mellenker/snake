#pragma once

#include "Game.hpp"
#include "PauseMenu.hpp"
// forward-declare State to avoid circular include (State.hpp also needs Context)
class State;
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <optional>

struct Context {
    //Context();
    sf::Keyboard::Key keyPressed = sf::Keyboard::Key::Unknown;
    std::optional<PauseMenu::Action> action;
    std::function<void(std::unique_ptr<State>)> changeState;
};
