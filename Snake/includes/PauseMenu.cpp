#include "includes/PauseMenu.h"
#include <SFML/Graphics.hpp>
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

// TESTA ATT IMPLEMENTERA LOGIKEN HÄR INNE?
void PauseMenu::performAction() {
	switch (highlightedIdx) {
	case 0:
		std::cout << "Unpause" << std::endl;
		// Unpause logic here
		/*
			Set gameState to PlAY
		*/
		break;
	case 1:
		std::cout << "Restart" << std::endl;
		// Restart logic here
		/*
			Delete snake and apple
			Re-create snake and apple
		*/
		break;
	case 2:
		std::cout << "Exit" << std::endl;
		// Exit logic here
		/*
			Close window (Should go back to main menu later)
		*/
		break;
	default:
		break;
	}
}
