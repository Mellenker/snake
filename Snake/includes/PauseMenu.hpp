#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Menu.hpp"
#include "includes/Utils.hpp"
#include <functional>

class PauseMenu : public Menu {
public:
	PauseMenu(int windowSizeX, int windowSizeY);
	const enum Action { NONE, UNPAUSE, RESTART, EXIT };
	PauseMenu::Action decideAction();
private:
};