#include "../includes/Menu.hpp"
#include "../includes/PauseMenu.hpp"
#include <iostream>

PauseMenu::PauseMenu()
	: Menu()
{
	setTitle("Paused");

	addItem("Unpause");
	addItem("Restart");
	addItem("Exit");
}

PauseMenu::Action PauseMenu::decideAction() 
{
	switch (highlightedIdx) {
	case 0:
		return Action::UNPAUSE;
		break;
	case 1:
		return Action::RESTART;
		break;
	case 2:
		return Action::EXIT;
		break;
	default:
		return Action::NONE;
		break;
	}
}

