#include "includes/Application.h"
#include "includes/Game.h"
#include <iostream>

using namespace sf;

/*
What should be handled:
- Wíndow
- Game loop
- Main menu
- App states: Main menu, Playing
*/


Application::Application()
	: inGameFPSLimit(10), menuFPSLimit(39), winSizeInTilesX(29), winSizeInTilesY(29)
{
	// Set window size based on tile size and map size
	std::map<char, int> gameMapSize = game.getMapSizeInTiles();
	int tileSize = game.getTileSize();
	window.create(VideoMode(gameMapSize['x'] * tileSize, gameMapSize['y'] * tileSize), "Snake Game");

	std::cout << "Creatied application with map size: " << gameMapSize['x'] * tileSize << " x " << gameMapSize['y'] * tileSize << std::endl;
	window.setTitle("Snake");
	window.setFramerateLimit(inGameFPSLimit);
	window.setKeyRepeatEnabled(false); // Holding down keys should not count as multiple presses

	std::cout << "APPLICATION CREATED\n";
}

void Application::runGameLoop() {
	// GAME LOOP
	while (window.isOpen()) {

		Event event;
		Event lastKeyPressedEvent;

		// Handle events
		if (window.pollEvent(event)) {
			lastKeyPressedEvent = event; // Needs to be initialized (Find other solution)
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				lastKeyPressedEvent = event;
			}

			// Drain the rest of the queue, keeping only the last KeyPressed event
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
					break;
				}
				if (event.type == Event::KeyPressed) {
					lastKeyPressedEvent = event;
				}
			}

			// Process only latest keyboard input
			if (lastKeyPressedEvent.type == Event::KeyPressed) {
				std::cout << "Key pressed" << std::endl;
				game.handleKeyboardInput(lastKeyPressedEvent.key.code);
			}

		}

		game.moveSnake();

		window.clear();

		// Draw game objects
		game.drawGameObjects(window);

		window.display();

	}
}



