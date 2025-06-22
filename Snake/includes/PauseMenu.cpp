#include "includes/PauseMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

void PauseMenu::performAction() {
	switch (highlightedIdx) {
	case 0:
		std::cout << "Unpause" << std::endl;
		// Unpause logic here
		break;
	case 1:
		std::cout << "Restart" << std::endl;
		// Restart logic here
		break;
	case 2:
		std::cout << "Exit" << std::endl;
		// Exit logic here
		break;
	default:
		break;
	}
}
