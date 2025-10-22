#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include "Game.hpp"
#include "Utils.hpp"
#include "PauseMenu.hpp"
#include "GameOverMenu.hpp"

class Application {
public:
	Application();
	void runGameLoop();
	sf::Keyboard::Key processEvent(bool isInMenu = false);
	std::optional<sf::Keyboard::Key> checkForLastKeyPressedEvent(const sf::Event& event);
	void processPauseMenuInput(sf::Keyboard::Key key);
	void processGameOverMenuInput(sf::Keyboard::Key key);
	void update(sf::Keyboard::Key keyPressed);
	void updatePlayState(sf::Keyboard::Key keyPressed);
	void updatePauseState(sf::Keyboard::Key keyPressed);
	void updateGameOverState(sf::Keyboard::Key keyPressed);
	void render();

private: 
	Game game; 
	sf::RenderWindow window;

	Utils::GameState gameState;
	PauseMenu pauseMenu;
	PauseMenu::Action pauseMenuAction;
	GameOverMenu gameOverMenu;
	GameOverMenu::Action gameOverMenuAction;

	static constexpr int maxFPS = 4;


};