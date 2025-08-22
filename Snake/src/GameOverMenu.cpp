#include "../includes/Menu.hpp"
#include "../includes/GameOverMenu.hpp"
#include <iostream>

GameOverMenu::GameOverMenu(int windowSizeX, int windowSizeY)
	: Menu(windowSizeX, windowSizeY)
{
	setTitle("Game Over");

	addItem("Restart");
	addItem("Exit");
}

GameOverMenu::Action GameOverMenu::decideAction() 
{
	switch (highlightedIdx) {
	case 0:
		return Action::RESTART;
		break;
	case 1:
		return Action::EXIT;
		break;
	default:
		return Action::NONE;
		break;
	}
}

