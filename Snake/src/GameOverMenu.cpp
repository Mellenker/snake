#include "includes/Menu.hpp"
#include "includes/GameOverMenu.hpp"
#include <iostream>

using namespace sf;

GameOverMenu::GameOverMenu(int windowSizeX, int windowSizeY)
	: Menu(windowSizeX, windowSizeY)
{
	setTitle("Game Over");

	addItem("Restart");
	addItem("Exit");
}

void GameOverMenu::performAction(RenderWindow& window, int chosenItemIdx, std::function<void()> restartGame) {
	switch (chosenItemIdx) {
	case 0:
		restartGame();
		break;
	case 1:
		window.close();
		break;
	default:
		break;
	}
}