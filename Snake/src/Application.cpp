#include "includes/Application.h"
#include "includes/Game.h"
#include <iostream>

using namespace sf;

Application::Application() {

	// Set window size based on tile size and map size
	std::map<char, int> gameMapSize = game.getMapSizeInTiles();
	int tileSize = game.getTileSize();
	window.create(VideoMode(gameMapSize['x'] * tileSize, gameMapSize['y'] * tileSize), "Snake Game");

	window.setTitle("Snake");
	window.setFramerateLimit(maxFPS);
	window.setKeyRepeatEnabled(false); // Holding down keys should not count as multiple presses

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

		game.drawGameObjects(window);
		game.handleGameState(window);

		window.display();

	}
}
