#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Menu.hpp"
#include "includes/State.hpp"
#include <functional>

class PauseMenu : public Menu {
public:
	PauseMenu(int windowSizeX, int windowSizeY);
	void performAction(
		sf::RenderWindow& window, 
		int selectedIdx, 
		std::function<void()> setGameState(State::GameState newState),
		std::function<void()> restartGame
	);
private:

};