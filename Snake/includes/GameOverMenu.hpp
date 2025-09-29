#pragma once

#include <SFML/Graphics.hpp>
#include "../includes/Menu.hpp"

class GameOverMenu : public Menu {
public:
	GameOverMenu();
	const enum Action { NONE, RESTART, EXIT };
	GameOverMenu::Action decideAction();
private:

};