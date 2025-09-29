#include "../includes/Application.hpp"

Application::Application()
	: game(),
	window(),
	gameState(Utils::GameState::PLAY),
	pauseMenu(),
	gameOverMenu()
{

	// Set window size based on tile size and map size
	window.create(sf::VideoMode(Utils::mapSizeInTilesX * Utils::tileSize, Utils::mapSizeInTilesY * Utils::tileSize), "Snake Game");

	window.setTitle("Snake");
	window.setFramerateLimit(maxFPS);
	window.setKeyRepeatEnabled(false); // Holding down keys should not count as multiple presses
}

void Application::runGameLoop() {

	while (window.isOpen()) {
		sf::Keyboard::Key keyPressed = processEvent();
		update(keyPressed);
		render();
	}
}

sf::Keyboard::Key Application::processEvent() {
	sf::Event event;

	if (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			window.close();
		}

		sf::Event lastKeyPressedEvent = checkForLastKeyPressedEvent(event);

		if (lastKeyPressedEvent.type != sf::Event::KeyPressed) {
			return sf::Keyboard::Key::Unknown;
		}

		// Process only latest keyboard input
		switch (gameState) {
		case Utils::GameState::PLAY:
			if (lastKeyPressedEvent.key.code == sf::Keyboard::Key::Escape) {
				gameState = Utils::GameState::PAUSED;
			}
			else {
				return lastKeyPressedEvent.key.code;
			}
			break;
		case Utils::GameState::PAUSED:
			processPauseMenuInput(lastKeyPressedEvent.key.code);
			break;

		case Utils::GameState::GAMEOVER:
			processGameOverMenuInput(lastKeyPressedEvent.key.code);
			break;

		default:
			break;
		}

	}

	return sf::Keyboard::Key::Unknown;
}

sf::Event Application::checkForLastKeyPressedEvent(sf::Event event) {
	sf::Event lastKeyPressedEvent;
	bool foundKeyPressed = false;

	// Check the first event
	if (event.type == sf::Event::KeyPressed) {
		lastKeyPressedEvent = event;
		foundKeyPressed = true;
	}

	// Drain the rest of the queue, keeping only the last KeyPressed event
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			break;
		}
		if (event.type == sf::Event::KeyPressed) {
			lastKeyPressedEvent = event;
			foundKeyPressed = true;
		}
	}

	if (foundKeyPressed) {
		return lastKeyPressedEvent;
	}
	else {
		// No KeyPressed event found, return original event
		return event;
	}
}

void Application::processPauseMenuInput(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Key::W:
		pauseMenu.moveUp();
		break;
	case sf::Keyboard::Key::S:
		pauseMenu.moveDown();
		break;
	case sf::Keyboard::Key::Enter:
		pauseMenuAction = pauseMenu.decideAction();
		break;
	case sf::Keyboard::Key::Escape:
		pauseMenuAction = PauseMenu::Action::UNPAUSE;
		break;
	default:
		break;
	}
}
void Application::processGameOverMenuInput(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Key::W:
		gameOverMenu.moveUp();
		break;
	case sf::Keyboard::Key::S:
		gameOverMenu.moveDown();
		break;
	case sf::Keyboard::Key::Enter:
		gameOverMenuAction = gameOverMenu.decideAction();
		break;
	default:
		break;
	}
}

void Application::update(sf::Keyboard::Key keyPressed) {

	switch (gameState) {
	case Utils::GameState::PLAY:
		updatePlayState(keyPressed);
		break;
	case Utils::GameState::PAUSED:
		updatePauseState(keyPressed);
		break;
	case Utils::GameState::GAMEOVER:
		updateGameOverState(keyPressed);
		break;
	default:
		break;
	}
}

void Application::updatePlayState(sf::Keyboard::Key keyPressed) {
	game.forwardSnakeInput(keyPressed);

	// Returns true if illegal move is attempted
	if (game.tryUpdateSnakeState()) {
		gameState = Utils::GameState::GAMEOVER;
	}

}

void Application::updatePauseState(sf::Keyboard::Key keyPressed) {
	switch (pauseMenuAction) {
	case PauseMenu::Action::UNPAUSE:
		gameState = Utils::GameState::PLAY;
		break;
	case PauseMenu::Action::RESTART:
		game.resetGame();
		gameState = Utils::GameState::PLAY;
		break;
	case PauseMenu::Action::EXIT:
		window.close();
		break;
	default:
		break;
	}

	pauseMenuAction = PauseMenu::Action::NONE; // Reset action
}

void Application::updateGameOverState(sf::Keyboard::Key keyPressed) {
	switch (gameOverMenuAction) {
	case GameOverMenu::Action::RESTART:
		game.resetGame();
		gameState = Utils::GameState::PLAY;
		break;
	case GameOverMenu::Action::EXIT:
		window.close();
		break;
		break;
	default:
		break;
	}

	gameOverMenuAction = GameOverMenu::Action::NONE; // Reset action
}

void Application::render() {
	window.clear();
	game.drawObjects(window);

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
