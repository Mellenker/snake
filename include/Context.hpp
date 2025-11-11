#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <optional>
#include <queue>
#include "State.hpp"
#include "Game.hpp"

struct Context {    
    sf::Keyboard::Scancode keyPressed = sf::Keyboard::Scancode::Unknown;
    std::queue<sf::Keyboard::Scancode> movementInputBuffer;
    std::function<void(State::StateID id)> changeState;
    bool closeWindow = false;
};