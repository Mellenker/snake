#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.hpp"

class GameOverMenu : public Menu {
public:
	GameOverMenu();
	enum Action { NONE, RESTART, EXIT };
	GameOverMenu::Action decideAction();
private:

};