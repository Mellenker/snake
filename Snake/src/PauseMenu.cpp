#include "includes/Menu.hpp"
#include "includes/PauseMenu.hpp"
#include <iostream>

using namespace sf;

PauseMenu::PauseMenu(int windowSizeX, int windowSizeY)
	: Menu(windowSizeX, windowSizeY)
{
	setTitle("Paused");

	addItem("Unpause");
	addItem("Restart");
	addItem("Exit");
}

void PauseMenu::performAction(
	RenderWindow& window,
	int chosenIdx,
	std::function<void()>
	setGameState(State::GameState newState),
	std::function<void()> restartGame
) 
{
	switch (chosenIdx) {
	case 0:
		setGameState(State::GameState::PLAY);
		break;
	case 1:
		restartGame();
		break;
	case 2:
		window.close();
		break;
	default:
		break;
	}
}