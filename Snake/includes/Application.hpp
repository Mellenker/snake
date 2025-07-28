#pragma once

#include <SFML/Graphics.hpp>
#include "includes/Game.hpp"

class Application {
public:
	Application();
	void runGameLoop();
private:
	Game game;

	sf::RenderWindow window;

	static constexpr int maxFPS = 10;
	static constexpr int winSizeInTilesX = 29;
	static constexpr int winSizeInTilesY = 29;
};