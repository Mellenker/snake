#include "includes/GameOverMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

GameOverMenu::GameOverMenu(int windowSizeX, int windowSizeY)
	: Menu(windowSizeX, windowSizeY)
{
	setTitle("Game Over");
	addItem("Restart");
	addItem("Exit");
}

void GameOverMenu::performAction() {
	switch (highlightedIdx) {
	case 0:
		std::cout << "Restart" << std::endl;
		// Restart logic here
		break;
	case 1:
		std::cout << "Exit" << std::endl;
		// Exit logic here
		break;
	default:
		break;
	}
}