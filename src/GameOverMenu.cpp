#include "GameOverMenu.hpp"

GameOverMenu::GameOverMenu() :
	Menu(72, 42)
{
	setTitle("Game Over");
	addItem("Restart");
	addItem("Exit");
}

GameOverMenu::Action GameOverMenu::decideAction() 
{
	switch (m_highlightedIdx) {
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

