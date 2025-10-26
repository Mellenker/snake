#include "Application.hpp"

#include <iostream>

Application::Application() : 
	pauseMenuAction(PauseMenu::Action::NONE),
	gameOverMenuAction(GameOverMenu::Action::NONE),
	currentState(std::make_unique<PlayingState>(window, game))
{
	// Build window
	window.create(sf::VideoMode({ Utils::mapSizeInTilesX * Utils::tileSize, Utils::mapSizeInTilesY * Utils::tileSize }), "Snake Game");
	window.setTitle("Snake");
	window.setFramerateLimit(maxFPS);
	window.setKeyRepeatEnabled(false); // Holding down keys should not count as multiple presses

	// Build context
	context.pauseMenu = &pauseMenu;
	context.gameOverMenu = &gameOverMenu;
	context.changeState = [this](std::unique_ptr<State> newState) {
		this->changeState(std::move(newState));
	};
}

void Application::runGameLoop() {

	while (window.isOpen()) {
		currentState->processInput(context);
		currentState->update(context);
		currentState->render(context);
	}
}

void Application::changeState(std::unique_ptr<State> newState) {
	currentState = std::move(newState);
}