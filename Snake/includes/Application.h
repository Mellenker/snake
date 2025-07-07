#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Game.h"

class Application {
public:
	Application();
	void runGameLoop();
private:
	Game game;

	sf::RenderWindow window;

	const int inGameFPSLimit;
	const int menuFPSLimit;
	const int winSizeInTilesX;
	const int winSizeInTilesY;
	

};