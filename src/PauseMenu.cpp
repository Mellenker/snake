#include "PauseMenu.hpp"

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
	switch (m_highlightedIdx) {
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

