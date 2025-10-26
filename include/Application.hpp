#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include "Game.hpp"
#include "Utils.hpp"
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"
#include "State.hpp"
#include "PlayingState.hpp"
#include "Context.hpp"

class Application {
public:
	Application();
	void runGameLoop();
	sf::Keyboard::Key processEvent(bool isInMenu = false);
	void processPauseMenuInput(sf::Keyboard::Key key);
	void processGameOverMenuInput(sf::Keyboard::Key key);
	void update(sf::Keyboard::Key keyPressed);
	void updatePlayState(sf::Keyboard::Key keyPressed);
	void updatePauseState(sf::Keyboard::Key keyPressed);
	void updateGameOverState(sf::Keyboard::Key keyPressed);
	void render();
	void changeState(std::unique_ptr<State> newState);

private: 
	Game game; 
	sf::RenderWindow window;

	Utils::GameState gameState;
	PauseMenu pauseMenu;
	PauseMenu::Action pauseMenuAction;
	GameOverMenu gameOverMenu;
	GameOverMenu::Action gameOverMenuAction;

	static constexpr int maxFPS = 4;

	std::unique_ptr<State> currentState;
};