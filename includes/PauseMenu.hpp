#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.hpp"

class PauseMenu : public Menu {
public:
	PauseMenu();
	enum Action { NONE, UNPAUSE, RESTART, EXIT };
	PauseMenu::Action decideAction();
private:

};