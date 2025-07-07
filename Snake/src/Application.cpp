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
	: window(VideoMode(800, 600), "Snake"), inGameFPSLimit(10), menuFPSLimit(39), winSizeInTilesX(29), winSizeInTilesY(29)
{
	std::cout << "APPLICATION CREATED\n";
}

void Application::runGameLoop() {
	// GAME LOOP
	while (window.isOpen()) {

		Event event;
		Event lastKeyPressedEvent;

		// Handle events
		if (window.pollEvent(event)) {
			lastKeyPressedEvent = event;
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

	}
}



