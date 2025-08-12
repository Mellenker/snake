#include "includes/Menu.hpp"
#include "includes/PauseMenu.hpp"
#include "includes/Utils.hpp"
#include <iostream>

/*
	ToDo:
		- Item list should be an ordered list of actions.
*/



using namespace sf;

PauseMenu::PauseMenu(int windowSizeX, int windowSizeY)
	: Menu(windowSizeX, windowSizeY)
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

