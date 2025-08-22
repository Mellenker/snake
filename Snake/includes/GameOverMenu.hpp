#pragma once

#include <SFML/Graphics.hpp>
#include "../includes/Menu.hpp"
#include <functional>

class GameOverMenu : public Menu {
public:
	GameOverMenu(int windowSizeX, int windowSizeY);
	const enum Action { NONE, RESTART, EXIT };
	GameOverMenu::Action decideAction();
private:

};