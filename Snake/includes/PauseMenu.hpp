#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Menu.hpp"
#include "includes/State.hpp"
#include <functional>

class PauseMenu : public Menu {
public:
	PauseMenu(int windowSizeX, int windowSizeY);
	const enum Action { UNPAUSE, RESTART, EXIT };
	Action show(sf::RenderWindow& window);
	PauseMenu::Action decideAction(int chosenIdx);
private:
	Action action;
};