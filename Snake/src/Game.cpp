#include "includes/Game.h"
#include <iostream>

using namespace sf;

/*
What should be handled:
- Game states: PLAY, PAUSED, GAMEOVER
- PAUSE MENU, GAMEOVER MENU
*/


Game::Game()
{
	std::cout << "Game created\n";
}

// Handle ingame keyboard input
void Game::handleKeyboardInput(Keyboard::Key keyPressed) {
	std::cout << "handleinput\n";
}



