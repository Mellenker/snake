#include "includes/Menu.hpp"
#include "includes/PauseMenu.hpp"
#include "includes/State.hpp"
#include <iostream>

/*
	ToDo:
		- Item list should be an ordered list of actions.
*/



using namespace sf;

PauseMenu::PauseMenu(int windowSizeX, int windowSizeY)
	: Menu(windowSizeX, windowSizeY)
{
	setTitle("Paused");

	addItem("Unpause");
	addItem("Restart");
	addItem("Exit");
}

// Returns action based on the highlighted menu item
PauseMenu::Action PauseMenu::show(RenderWindow& window) {

	draw(window);
	window.display();

	// PAUSE MENU LOOP
	while (window.isOpen()) {
		Event event;
		Event lastKeyPressedEvent;

		// Block until at least one event is available
		if (window.waitEvent(event)) {
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

			// Process only the latest event
			if (lastKeyPressedEvent.type == Event::KeyPressed) {
				switch (lastKeyPressedEvent.key.code) {
				case Keyboard::Key::W:
					moveUp();
					break;
				case Keyboard::Key::S:
					moveDown();
					break;
				case Keyboard::Key::Enter:
					std::cout << "Selected menu item: " << getHighlightedIdx() << std::endl;
					return decideAction(getHighlightedIdx());
					break;
				case Keyboard::Key::Escape:
					return Action::UNPAUSE;
					break;
				default:
					break;
				}
			}

			//std::cout << "FRAME" << std::endl;

			// Clear window
			window.clear();

			// Draw changes
			draw(window);
			window.display();

		}
	}
}



PauseMenu::Action PauseMenu::decideAction(int chosenIdx) 
{
	switch (chosenIdx) {
	case 0:
		return Action::UNPAUSE;
		break;
	case 1:
		return Action::RESTART;
		break;
	case 2:
		return Action::EXIT;
		break;
	default:
		break;
	}
}

