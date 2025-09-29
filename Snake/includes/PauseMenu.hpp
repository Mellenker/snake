#pragma once

#include <SFML/Graphics.hpp>
#include "../includes/Menu.hpp"

class PauseMenu : public Menu {
public:
	PauseMenu();
	const enum Action { NONE, UNPAUSE, RESTART, EXIT };
	PauseMenu::Action decideAction();
private:

};