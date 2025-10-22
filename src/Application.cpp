#include "Application.hpp"

#include <iostream>

Application::Application()
	: game(),
	window(),
	gameState(Utils::GameState::PLAY),
	pauseMenu(),
	pauseMenuAction(PauseMenu::Action::NONE),
	gameOverMenu(),
	gameOverMenuAction(GameOverMenu::Action::NONE)
{
	// Set window size based on tile size and map size
	window.create(sf::VideoMode({ Utils::mapSizeInTilesX * Utils::tileSize, Utils::mapSizeInTilesY * Utils::tileSize }), "Snake Game");

	window.setTitle("Snake");
	window.setFramerateLimit(maxFPS);
	window.setKeyRepeatEnabled(false); // Holding down keys should not count as multiple presses
}

void Application::runGameLoop() {

	while (window.isOpen()) {
		// Block for events only when in menus to avoid busy waiting
		bool isInMenu = (gameState == Utils::GameState::PAUSED || gameState == Utils::GameState::GAMEOVER);
		sf::Keyboard::Key keyPressed = processEvent(isInMenu);
		update(keyPressed);
		render();
		std::cout << "FRAME" << "\n";
	}
}

sf::Keyboard::Key Application::processEvent(bool isInMenu) {

	std::optional<sf::Event> lastKeyPressedEvent = std::nullopt;

	auto handleEvent = [&](const sf::Event& ev) {
		if (ev.is<sf::Event::Closed>()) {
			window.close();
			return;
		}
		if (ev.is<sf::Event::KeyPressed>()) {
			lastKeyPressedEvent = ev;
		}
	};

	if (isInMenu) {
		// Ensure no busy waiting in menus
		if (const std::optional<sf::Event> ev = window.waitEvent()) {
			handleEvent(ev.value());
			// Drain any additional events in queue, keep latest key pressed
			while (const std::optional<sf::Event> pe = window.pollEvent()) {
				handleEvent(pe.value());
			}
		}
	} else {
		while (const std::optional<sf::Event> ev = window.pollEvent()) {
			handleEvent(ev.value());
		}
	}

	if (!lastKeyPressedEvent) {
		return sf::Keyboard::Key::Unknown; // No key was pressed
	}
	else {
		// Process only latest keyboard input
		sf::Keyboard::Key keyCode = lastKeyPressedEvent->getIf<sf::Event::KeyPressed>()->code;
		switch (gameState) {
		case Utils::GameState::PLAY:
			if (keyCode == sf::Keyboard::Key::Escape) {
				gameState = Utils::GameState::PAUSED;
			}
			else {
				return keyCode;
			}
			break;
		case Utils::GameState::PAUSED:
			processPauseMenuInput(keyCode);
			break;

		case Utils::GameState::GAMEOVER:
			processGameOverMenuInput(keyCode);
			break;

		default:
			break;
		}
	}

	return sf::Keyboard::Key::Unknown; // No key was pressed
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
