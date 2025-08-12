#include "includes/Application.hpp"

#include <iostream>

Application::Application()
	: game(),
	window(),
	gameState(Utils::GameState::PLAY),
	pauseMenu(Utils::mapSizeInTilesX* Utils::tileSize, Utils::mapSizeInTilesY* Utils::tileSize),
	gameOverMenu(Utils::mapSizeInTilesX* Utils::tileSize, Utils::mapSizeInTilesY* Utils::tileSize)
{

	// Set window size based on tile size and map size
	window.create(sf::VideoMode(Utils::mapSizeInTilesX * Utils::tileSize, Utils::mapSizeInTilesY * Utils::tileSize), "Snake Game");

	window.setTitle("Snake");
	window.setFramerateLimit(maxFPS);
	window.setKeyRepeatEnabled(false); // Holding down keys should not count as multiple presses

}

void Application::runGameLoop() {
	// GAME LOOP
	while (window.isOpen()) {

		// What if no key is pressed?
		sf::Keyboard::Key keyPressed = processEvent();
		update(keyPressed);
		render();

	}
}

sf::Keyboard::Key Application::processEvent() {
	sf::Event event;
	sf::Event lastKeyPressedEvent;

	// Handle events (Place this in its own function?)
	if (window.pollEvent(event)) {
		lastKeyPressedEvent = event; // Needs to be initialized (Find other solution)
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			lastKeyPressedEvent = event;
		}

		// Drain the rest of the queue, keeping only the last KeyPressed event
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed) {
				lastKeyPressedEvent = event;
			}
		}

		// Process only latest keyboard input
		if (lastKeyPressedEvent.type == sf::Event::KeyPressed) {
			std::cout << "Key pressed" << std::endl;

			switch (gameState) {
			case Utils::GameState::PLAY:
				if (lastKeyPressedEvent.key.code == sf::Keyboard::Key::Escape) {
					gameState = Utils::GameState::PAUSED;
					std::cout << "PAUSED GAME\n";
				}
				else {
					return lastKeyPressedEvent.key.code;
				}
				break;
			case Utils::GameState::PAUSED:

				switch (lastKeyPressedEvent.key.code) {
				case sf::Keyboard::Key::W:
					pauseMenu.moveUp();
					break;
				case sf::Keyboard::Key::S:
					pauseMenu.moveDown();
					break;
				case sf::Keyboard::Key::Enter:
					std::cout << "Selected menu item: " << pauseMenu.getHighlightedIdx() << std::endl;
					pauseMenuAction = pauseMenu.decideAction();
					break;
				case sf::Keyboard::Key::Escape:
					pauseMenuAction = PauseMenu::Action::UNPAUSE;
					break;
				default:
					break;
				}

			case Utils::GameState::GAMEOVER:
				
				switch (lastKeyPressedEvent.key.code) {
				case sf::Keyboard::Key::W:
					gameOverMenu.moveUp();
					break;
				case sf::Keyboard::Key::S:
					gameOverMenu.moveDown();
					break;
				case sf::Keyboard::Key::Enter:
					std::cout << "Selected menu item: " << gameOverMenu.getHighlightedIdx() << std::endl;
					gameOverMenuAction = gameOverMenu.decideAction();
					break;
				default:
					break;
				}

			default:
				break;
			}

		}

	}

	return sf::Keyboard::Key::Unknown; // Return an unknown key if no key was pressed

}

// Divide into multiple functions later
void Application::update(sf::Keyboard::Key keyPressed) {

	switch (gameState) {
	case Utils::GameState::PLAY:
		std::cout << "Forward Snake Input\n";
		game.forwardSnakeInput(keyPressed);

		// Returns true if illegal move is attempted
		if (game.tryUpdateSnakeState()) {
			gameState = Utils::GameState::GAMEOVER;
			std::cout << "GAME OVER\n";
		}

		break;

	case Utils::GameState::PAUSED:
		// Handle pause menu action

		switch (pauseMenuAction) {
		case PauseMenu::Action::UNPAUSE:
			gameState = Utils::GameState::PLAY;
			std::cout << "UNPAUSED GAME\n";
			break;
		case PauseMenu::Action::RESTART:
			game.resetGame();
			gameState = Utils::GameState::PLAY;
			std::cout << "RESTARTED GAME\n";
			break;
		case PauseMenu::Action::EXIT:
			window.close();
			break;
		default:
			break;
		}

		pauseMenuAction = PauseMenu::Action::NONE;

	case Utils::GameState::GAMEOVER:

		// Handle game over menu actions
		switch (gameOverMenuAction) {
		case GameOverMenu::Action::RESTART:
			game.resetGame();
			gameState = Utils::GameState::PLAY;
			std::cout << "RESTARTED GAME\n";
			break;
		case GameOverMenu::Action::EXIT:
			window.close();
			break;
		break;
		default:
			break;
		}

		gameOverMenuAction = GameOverMenu::Action::NONE;

	default:
		break;
	}
}

void Application::render() {
	window.clear();
	game.drawGameObjects(window);

	switch (gameState) {
	case Utils::GameState::PAUSED:
		pauseMenu.draw(window);
		break;
	case Utils::GameState::GAMEOVER:
		gameOverMenu.draw(window);
		break;
	default:
		break;
	}
	window.display();
}
